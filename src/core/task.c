/**
 * @file task.h
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for handling groups.
 */

#include "core/task.h"

#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating an AttendanceTask struct.
 *
 * @param n : string pointer
 * @param d : Date struct
 * @return A pointer to the AttendanceTask struct
 */
AttendanceTask* createAttendanceTask(const char* n, Date d) {
    AttendanceTask* task = (AttendanceTask*)malloc(sizeof(AttendanceTask));

    task->base.destroy = destroyAttendanceTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_ATTENDANCE;
    task->grade = -1;

    return task;
}

void destroyAttendanceTask(Task* self) { free(self); }

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating a ChoreTask struct.
 *
 * @param n : string pointer
 * @param d : Date struct
 * @return A pointer to the ChoreTask struct
 */
ChoreTask* createChoreTask(const char* n, Date d) {
    ChoreTask* task = (ChoreTask*)malloc(sizeof(ChoreTask));

    task->base.destroy = destroyChoreTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_CHORE;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for destroying a ChoreTask struct.
 *
 * @param self : Task struct pointer
 */
void destroyChoreTask(Task* self) { free(self); }

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating an ExamTask struct.
 *
 * @param n : string pointer
 * @param d : Date struct
 * @return A pointer to the ExamTask struct
 */
ExamTask* createExamTask(const char* n, Date d) {
    ExamTask* task = (ExamTask*)malloc(sizeof(ExamTask));

    task->base.destroy = destroyExamTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_EXAM;
    task->grade = -1;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for destroying an ExamTask struct.
 *
 * @param self : Task struct pointer
 */
void destroyExamTask(Task* self) { free(self); }

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating a HomeworkTask struct.
 *
 * @param n : string pointer
 * @param d : Date struct
 * @return A pointer to the HomeworkTask struct
 */
HomeworkTask* createHomeworkTask(const char* n, Date d) {
    HomeworkTask* task = (HomeworkTask*)malloc(sizeof(HomeworkTask));

    task->base.destroy = destroyHomeworkTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_HW;
    task->grade = -1;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for destroying a HomeworkTask struct.
 *
 * @param self : Task struct pointer
 */
void destroyHomeworkTask(Task* self) { free(self); }

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating a QuizTask struct.
 *
 * @param n : string pointer
 * @param d : Date struct
 * @return A pointer to the QuizTask struct
 */
QuizTask* createQuizTask(const char* n, Date d) {
    QuizTask* task = (QuizTask*)malloc(sizeof(QuizTask));

    task->base.destroy = destroyQuizTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_QUIZ;
    task->grade = -1;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for destroying a QuizTask struct.
 *
 * @param self : Task struct pointer
 */
void destroyQuizTask(Task* self) { free(self); }

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating a ReadingTask struct.
 *
 * @param n : string pointer
 * @param d : Date struct
 * @return A pointer to the ReadingTask struct
 */
ReadingTask* createReadingTask(const char* n, Date d) {
    ReadingTask* task = (ReadingTask*)malloc(sizeof(ReadingTask));

    task->base.destroy = destroyReadingTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_READING;
    task->grade = -1;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for destroying a ReadingTask struct.
 *
 * @param self : Task struct pointer
 */
void destroyReadingTask(Task* self) { free(self); }

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating a PresentationTask struct.
 *
 * @param n : string pointer
 * @param d : Date struct
 * @return A pointer to the PresentationTask struct
 */
PresentationTask* createPresentationTask(const char* n, Date d) {
    PresentationTask* task =
        (PresentationTask*)malloc(sizeof(PresentationTask));

    task->base.destroy = destroyPresentationTask;
    task->base.dueDate = d;
    task->base.name = n;
    task->base.type = T_TYPE_PRESENTATION;
    task->grade = -1;

    return task;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for destroying a PresentationTask struct.
 *
 * @param self : Task struct pointer
 */
void destroyPresentationTask(Task* self) { free(self); }
