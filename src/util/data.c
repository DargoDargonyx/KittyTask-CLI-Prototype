/**
 * @file data.c
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for handling data and
 * managing the sqlite database.
 */

#include "util/data.h"
#include "external/sqlite3.h"
#include "util/error.h"

#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating a DataManager struct.
 *
 * @param filename : c-style string
 * @return A pointer to the newly created DataManager struct
 */
DataManager* createDataManager(const char* filename) {
    DataManager* manager = (DataManager*) malloc(sizeof(DataManager));
    if (!manager) return NULL;

    manager->db = NULL;
    if (sqlite3_open(filename, &manager->db) != SQLITE_OK) {
        free(manager);
        return NULL;
    }

    manager->errCount = DATA_ERR_INIT_CAP;
    manager->errs = (Error*) calloc(manager->errCount, sizeof(Error));
    if (!manager->errs) {
        sqlite3_close(manager->db);
        free(manager);
        return NULL;
    }

    return manager;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying a DataManager struct.
 *
 * @param self : DataManager struct pointer
 * @return An Error struct describing whether or not the 
 * DataManager struct was successfully destroyed
 */
Error destroyDataManager(DataManager* self) {
    if (!self) return createError(
			ESTAT_DATA_MANAGER_DESTROY,
			"Could not destroy a NULL data manager");

    if (!self->db) return createError(
			ESTAT_DATA_MANAGER_DESTROY,
			"Could not destory a data manager with no db field");
    
	if (!self->errs) return createError(
			ESTAT_DATA_MANAGER_DESTROY,
			"Could not destory a data manager with no error array field");
    
	sqlite3_close(self->db);
    free(self->errs);
    free(self);
	return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for adding an Error struct to
 * a DataManager struct.
 *
 * @param tracker : DataManager struct pointer
 * @param err : Error struct
 * @return An Error struct describing whether or not a new Error
 * was able to be successfuly added to the DataManager struct
 */
Error addDataError(DataManager* manager, Error err) {
    if (!manager) return createError(
			ESTAT_DATA_MANAGER_ADD_ERR,
			"Could not add an Error to a NULL data manager");
	if (!manager->errs) return createError(
			ESTAT_DATA_MANAGER_ADD_ERR, 
			"Could not add an Error to a data manager with a NULL \
			Error array field");

	if (manager->errCount == manager->errCap) {
        manager->errCap = (manager->errCount + 1) * 2;
        Error* orig = manager->errs;
		Error* temp = (Error*) calloc(manager->errCap, sizeof(Error));
        if (!temp) return createError(
				ESTAT_DATA_MANAGER_ADD_ERR, 
				"Could not reallocate a larger Error array field");
		
		for (int i = 0; i < manager->errCount; i++) {
            temp[i] = orig[i];
        }
        free(orig);
        manager->errs = temp;
    }

    manager->errs[manager->errCount] = err;
    manager->errCount++;
	return createError(ESTAT_MAIN_NONE, NULL);
}
