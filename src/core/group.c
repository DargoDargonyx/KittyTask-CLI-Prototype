/**
 * @file group.c
 * @author DargoDargonyx
 * @date 03/27/2026
 * @brief Handles the logic for handling groups.
 */

#define INIT_TASK_CAP 31

#include "core/group.h"

#include <stdlib.h>

ClassGroup* createClassGroup(const char* n, int sem, int top, int y) {
    ClassGroup* grp = (ClassGroup*)malloc(sizeof(ClassGroup));

    grp->base.destroy = destroyClassGroup;
    grp->base.name = n;
    grp->base.type = G_TYPE_CLASS;
    grp->base.taskCap = INIT_TASK_CAP;
    grp->base.taskCount = 0;
    grp->base.tasks = (Task**)calloc(INIT_TASK_CAP, sizeof(Task*));

    grp->grade = 0;
    grp->semester = sem;
    grp->topic = top;
    grp->year = y;

    return grp;
}

void destroyClassGroup(Group* self) {
    for (int i = 0; i < self->taskCount; i++) {
        Task* temp = self->tasks[i];
        temp->destroy(temp);
    }
    free(self);
}

DevGroup* createDevGroup(const char* n, int top, int y) {
    DevGroup* grp = (DevGroup*)malloc(sizeof(DevGroup));

    grp->base.destroy = destroyDevGroup;
    grp->base.name = n;
    grp->base.type = G_TYPE_DEV;
    grp->base.taskCap = INIT_TASK_CAP;
    grp->base.taskCount = 0;
    grp->base.tasks = (Task**)calloc(INIT_TASK_CAP, sizeof(Task*));

    grp->topic = top;
    grp->year = y;

    return grp;
}

void destroyDevGroup(Group* self) {
    for (int i = 0; i < self->taskCount; i++) {
        Task* temp = self->tasks[i];
        temp->destroy(temp);
    }
    free(self);
}

ResearchGroup* createResearchGroup(const char* n, int top, int y) {
    ResearchGroup* grp = (ResearchGroup*)malloc(sizeof(ResearchGroup));

    grp->base.destroy = destroyResearchGroup;
    grp->base.name = n;
    grp->base.type = G_TYPE_RESEARCH;
    grp->base.taskCap = INIT_TASK_CAP;
    grp->base.taskCount = 0;
    grp->base.tasks = (Task**)calloc(INIT_TASK_CAP, sizeof(Task*));

    grp->topic = top;
    grp->year = y;

    return grp;
}

void destroyResearchGroup(Group* self) {
    for (int i = 0; i < self->taskCount; i++) {
        Task* temp = self->tasks[i];
        temp->destroy(temp);
    }
    free(self);
}
