/**
 * @file task.h
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for handling groups.
 */

#include "core/task.h"

#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 03/29/26
 * @brief Handles the logic for destroying any Task struct.
 *
 * @param self : Task struct pointer
 * @return An Error struct that describes whether or not the
 * Task struct was able to successfully be destroyed
 */
Error destroyTask(Task* self) {
	return self->destroy(self);
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating an AttendanceTask struct.
 *
 * @param n : c-style string
 * @param d : Date struct
 * @return A pointer to the AttendanceTask struct
 */
AttendanceTask* createAttendanceTask(const char* n, Date d) {
    AttendanceTask* task = (AttendanceTask*) malloc(sizeof(AttendanceTask));

    task->base.destroy = destroyAttendanceTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_ATTENDANCE;
    task->grade = -1;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying an AttendanceTask struct.
 *
 * @param self : Task struct pointer
 * @return An Error struct that describes whether or not the 
 * AttendanceTask struct was successfully destroyed
 */
Error destroyAttendanceTask(Task* self) {
	if (!self) return createError(
			ESTAT_TASK_DESTROY,
			"Could not destroy a NULL attendance task");

	free(self);
	return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating a ChoreTask struct.
 *
 * @param n : c-style string
 * @param d : Date struct
 * @return A pointer to the newly created ChoreTask struct
 */
ChoreTask* createChoreTask(const char* n, Date d) {
    ChoreTask* task = (ChoreTask*) malloc(sizeof(ChoreTask));

    task->base.destroy = destroyChoreTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_CHORE;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying a ChoreTask struct.
 *
 * @param self : Task struct pointer
 * @return An Error struct that describes whether or not the
 * ChoreTask struct was successfully destroyed
 */
Error destroyChoreTask(Task* self) { 
	if (!self) return createError(
			ESTAT_TASK_DESTROY,
			"Could not destroy a NULL chore task");

	free(self);
	return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating an ExamTask struct.
 *
 * @param n : c-style string
 * @param d : Date struct
 * @return A pointer to the newly created ExamTask struct
 */
ExamTask* createExamTask(const char* n, Date d) {
    ExamTask* task = (ExamTask*) malloc(sizeof(ExamTask));

    task->base.destroy = destroyExamTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_EXAM;
    task->grade = -1;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying an ExamTask struct.
 *
 * @param self : Task struct pointer
 * @return An Error struct that describes whether or not the
 * ExamTask struct was successfully destroyed
 */
Error destroyExamTask(Task* self) { 
	if (!self) return createError(
			ESTAT_TASK_DESTROY,
			"Could not destroy a NULL exam task");
	
	free(self);
	return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating a HomeworkTask struct.
 *
 * @param n : c-style string
 * @param d : Date struct
 * @return A pointer to the newly created HomeworkTask struct
 */
HomeworkTask* createHomeworkTask(const char* n, Date d) {
    HomeworkTask* task = (HomeworkTask*) malloc(sizeof(HomeworkTask));

    task->base.destroy = destroyHomeworkTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_HW;
    task->grade = -1;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying a HomeworkTask struct.
 *
 * @param self : Task struct pointer
 * @return An Error struct that describes whether or not the
 * HomeworkTask struct was successfully destroyed
 */
Error destroyHomeworkTask(Task* self) {
	if (!self) return createError(
			ESTAT_TASK_DESTROY,
			"Could not destroy a NULL homework task");

	free(self);
	return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating a QuizTask struct.
 *
 * @param n : c-style string
 * @param d : Date struct
 * @return A pointer to the newly created QuizTask struct
 */
QuizTask* createQuizTask(const char* n, Date d) {
    QuizTask* task = (QuizTask*) malloc(sizeof(QuizTask));

    task->base.destroy = destroyQuizTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_QUIZ;
    task->grade = -1;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying a QuizTask struct.
 *
 * @param self : Task struct pointer
 * @return An Error struct that describes whether or not the
 * QuizTask struct was successfully destroyed
 */
Error destroyQuizTask(Task* self) {
	if (!self) return createError(
			ESTAT_TASK_DESTROY,
			"Could not destroy a NULL quiz task");

	free(self);
	return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating a ReadingTask struct.
 *
 * @param n : c-style string
 * @param d : Date struct
 * @return A pointer to the newly created ReadingTask struct
 */
ReadingTask* createReadingTask(const char* n, Date d) {
    ReadingTask* task = (ReadingTask*) malloc(sizeof(ReadingTask));

    task->base.destroy = destroyReadingTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_READING;
    task->grade = -1;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying a ReadingTask struct.
 *
 * @param self : Task struct pointer
 * @return An Error struct that describes whether or not the
 * ReadingTask struct was successfully destroyed
 */
Error destroyReadingTask(Task* self) {
	if (!self) return createError(
			ESTAT_TASK_DESTROY,
			"Could not destroy a NULL reading task");

	free(self);
	return createError(ESTAT_MAIN_NONE, NULL);
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for creating a PresentationTask struct.
 *
 * @param n : c-style string
 * @param d : Date struct
 * @return A pointer to the newly created PresentationTask struct
 */
PresentationTask* createPresentationTask(const char* n, Date d) {
    PresentationTask* task =
        (PresentationTask*) malloc(sizeof(PresentationTask));

    task->base.destroy = destroyPresentationTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_PRESENTATION;
    task->grade = -1;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for destroying a PresentationTask struct.
 *
 * @param self : Task struct pointer
 * @return An Error struct that describes whether or not the
 * PresentationTask struct was successfully destroyed
 */
Error destroyPresentationTask(Task* self) {
	if (!self) return createError(
			ESTAT_TASK_DESTROY,
			"Could not destroy a NULL presentation task");

	free(self);
	return createError(ESTAT_MAIN_NONE, NULL);
}
