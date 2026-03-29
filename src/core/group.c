/**
 * @file group.c
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for handling groups.
 */

#define INIT_TASK_CAP 31

#include "core/group.h"

#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating a ClassGroup struct.
 *
 * @param n : c-style string
 * @param sem : integer
 * @param topic : integer
 * @param y : integer
 * @return A pointer to the ClassGroup struct
 */
ClassGroup* createClassGroup(const char* n, int sem, int top, int y) {
    ClassGroup* grp = (ClassGroup*) malloc(sizeof(ClassGroup));

    grp->base.destroy = destroyClassGroup;
    grp->base.name = n;
    grp->base.type = G_TYPE_CLASS;
    grp->base.taskCap = INIT_TASK_CAP;
    grp->base.taskCount = 0;
    grp->base.tasks = (Task**) calloc(INIT_TASK_CAP, sizeof(Task*));

    grp->grade = -1;
    grp->semester = sem;
    grp->topic = top;
    grp->year = y;

    return grp;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying a ClassGroup struct.
 *
 * @param self : Group struct pointer
 * @return An Error struct that describes whether or not the 
 * ClassGroup struct was successfully destroyed
 */
Error destroyClassGroup(Group* self) {
    if (!self) return createError(
			ESTAT_GROUP_DESTROY,
			"Could not destory a NULL class group");
	if (!self->tasks) return createError(
			ESTAT_GROUP_DESTROY,
			"Could not destroy a class group without a task array");

	for (int i = 0; i < self->taskCount; i++) {
        Task* temp = self->tasks[i];
        temp->destroy(temp);
    }
    
	free(self);
	return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating a DevGroup struct.
 *
 * @param n : c-style string
 * @param sem : integer
 * @param y : integer
 * @return A pointer to the DevGroup struct
 */
DevGroup* createDevGroup(const char* n, int top, int y) {
    DevGroup* grp = (DevGroup*) malloc(sizeof(DevGroup));

    grp->base.destroy = destroyDevGroup;
    grp->base.name = n;
    grp->base.type = G_TYPE_DEV;
    grp->base.taskCap = INIT_TASK_CAP;
    grp->base.taskCount = 0;
    grp->base.tasks = (Task**) calloc(INIT_TASK_CAP, sizeof(Task*));

    grp->topic = top;
    grp->year = y;

    return grp;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying a DevGroup struct.
 *
 * @param self : Group struct pointer
 * @return An Error struct that describes whether or not the 
 * DevGroup struct was successfully destroyed
 */
Error destroyDevGroup(Group* self) {
    if (!self) return createError(
			ESTAT_GROUP_DESTROY,
			"Could not destory a NULL dev group");
	if (!self->tasks) return createError(
			ESTAT_GROUP_DESTROY,
			"Could not destroy a dev group without a task array");

	for (int i = 0; i < self->taskCount; i++) {
        Task* temp = self->tasks[i];
        temp->destroy(temp);
    }
    
	free(self);
	return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating a ResearchGroup struct.
 *
 * @param n : c-style string
 * @param topic : integer
 * @param y : integer
 * @return A pointer to the ResearchGroup struct
 */
ResearchGroup* createResearchGroup(const char* n, int top, int y) {
    ResearchGroup* grp = (ResearchGroup*) malloc(sizeof(ResearchGroup));

    grp->base.destroy = destroyResearchGroup;
    grp->base.name = n;
    grp->base.type = G_TYPE_RESEARCH;
    grp->base.taskCap = INIT_TASK_CAP;
    grp->base.taskCount = 0;
    grp->base.tasks = (Task**) calloc(INIT_TASK_CAP, sizeof(Task*));

    grp->topic = top;
    grp->year = y;

    return grp;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying a ResearchGroup struct.
 *
 * @param self : Group struct pointer
 * @return An Error struct that describes whether or not the 
 * ResearchGroup struct was successfully destroyed
 */
Error destroyResearchGroup(Group* self) {
    if (!self) return createError(
			ESTAT_GROUP_DESTROY,
			"Could not destory a NULL research group");
	if (!self->tasks) return createError(
			ESTAT_GROUP_DESTROY,
			"Could not destroy a research group without a task array");

    for (int i = 0; i < self->taskCount; i++) {
        Task* temp = self->tasks[i];
        temp->destroy(temp);
    }
    
	free(self);
	return createError(ESTAT_MAIN_NONE, NULL);
}
