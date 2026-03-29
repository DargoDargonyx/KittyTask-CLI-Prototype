/**
 * @file group.c
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for handling groups.
 */


#include "core/group.h"

#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 03/29/26
 * @brief Handles the logic for destroying any Group struct.
 *
 * @param self : Group struct pointer
 * @return An Error struct that describes whether or not the
 * Group struct was able to successfully be destroyed
 */
Error destroyGroup(Group* self) {
	return self->destroy(self);
}

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

	Error err = createError(ESTAT_MAIN_NONE, NULL);
	for (int i = 0; i < self->taskCount; i++) {
		err = destroyTask(self->tasks[i]);
		if (err.statusNum != ESTAT_MAIN_NONE) return err;
    }
    
	free(self);
	return err;
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

	Error err = createError(ESTAT_MAIN_NONE, NULL);
	for (int i = 0; i < self->taskCount; i++) {
		err = destroyTask(self->tasks[i]);
		if (err.statusNum != ESTAT_MAIN_NONE) return err;
    }
    
	free(self);
	return err;
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
			"Could not destroy a NULL research group");
	if (!self->tasks) return createError(
			ESTAT_GROUP_DESTROY,
			"Could not destroy a research group without a task array");

	Error err = createError(ESTAT_MAIN_NONE, NULL);
    for (int i = 0; i < self->taskCount; i++) {
		err = destroyTask(self->tasks[i]);
		if (err.statusNum != ESTAT_MAIN_NONE) return err;
    }
    
	free(self);
	return err;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating a GroupContainer struct.
 *
 * @return A pointer to the ResearchGroup struct
 */
GroupContainer* createGroupContainer() {
	GroupContainer* container = 
		(GroupContainer*) malloc(sizeof(GroupContainer));

	container->groupCap = INIT_GROUP_CAP;
	container->groupCount = 0;
	container->groups = 
		(Group**) calloc(container->groupCap, sizeof(Group*));

	return container;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying a GroupContainer struct.
 *
 * @param self : GroupContainer struct pointer
 * @return An Error struct that describes whether or not the 
 * ResearchGroup struct was successfully destroyed
 */
Error destroyGroupContainer(GroupContainer* self) {
	if (!self) return createError(
			ESTAT_GROUP_CONTAINER_DESTROY,
			"Could not destroy a NULL group container");
	if (!self->groups) return createError(
			ESTAT_GROUP_CONTAINER_DESTROY,
			"Could not destroy a group container without a group array");
	
	Error err = createError(ESTAT_MAIN_NONE, NULL);
	for (int i = 0; i < self->groupCount; i++) {
		err = destroyGroup(self->groups[i]);
		if (err.statusNum != ESTAT_MAIN_NONE) return err;
	}
	
	free(self);
	return err;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for adding a Task struct to
 * a Group struct.
 *
 * @param group : Group struct pointer
 * @param task : Task struct pointer
 * @return An Error struct that describes whether or not the 
 * Task struct was successfully added to the Group struct
 */
Error addTask(Group* group, Task* task) {
	if (!group) return createError(
			ESTAT_GROUP_ADD_TASK,
			"Could not add a task to a NULL group");
	if (!task) return createError(
			ESTAT_GROUP_ADD_TASK,
			"Could not add a NULL task to a group");

	if (group->taskCount == group->taskCap) {
        group->taskCap = (group->taskCount + 1) * 2;
        Task** orig = group->tasks;
        Task** temp = (Task**) calloc(group->taskCap, sizeof(Task*));
        if (!temp) return createError(
				ESTAT_GROUP_ADD_TASK, 
				"Could not reallocate a larger Task array field");
        
		for (int i = 0; i < group->taskCount; i++) {
            temp[i] = orig[i];
        }
        free(orig);
        group->tasks = temp;
    }

    group->tasks[group->taskCount] = task;
    group->taskCount++;
	return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for adding a Group struct to
 * a GroupContainer struct.
 *
 * @param container : GroupContainer struct pointer
 * @param group : Group struct pointer
 * @return An Error struct that describes whether or not the 
 * Group struct was successfully added to the GroupContainer struct
 */
Error addGroup(GroupContainer* container, Group* group) {
	if (!container) return createError(
			ESTAT_GROUP_CONTAINER_ADD_GROUP,
			"Could not add a group to a NULL group container");
	if (!group) return createError(
			ESTAT_GROUP_CONTAINER_ADD_GROUP,
			"Could not add a NULL group to a group container");

	if (container->groupCount == container->groupCap) {
        container->groupCap = (container->groupCount + 1) * 2;
        Group** orig = container->groups;
        Group** temp = (Group**) calloc(container->groupCap, sizeof(Group*));
        if (!temp) return createError(
				ESTAT_GROUP_CONTAINER_ADD_GROUP, 
				"Could not reallocate a larger Group array field");
        
		for (int i = 0; i < container->groupCount; i++) {
            temp[i] = orig[i];
        }
        free(orig);
        container->groups = temp;
    }

    container->groups[container->groupCount] = group;
    container->groupCount++;
	return createError(ESTAT_MAIN_NONE, NULL);
}
