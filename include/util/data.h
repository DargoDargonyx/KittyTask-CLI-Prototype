/**
 * @file data.h
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for handling data and
 * managing the sqlite database.
 */

#ifndef DATA_H
#define DATA_H

#define DATA_ERR_INIT_CAP 15

#include "external/sqlite3.h"
#include "util/error.h"

typedef struct {
    sqlite3* db;
    int errCap;
    int errCount;
    Error* errs;
} DataManager;

DataManager* createDataManager(const char* filename);
Error destroyDataManager(DataManager* self);
Error addDataError(DataManager* manager, Error err);

#endif
