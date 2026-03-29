/**
 * @file task.h
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for handling tasks.
 */

#ifndef TASK_H
#define TASK_H

// types
#define T_TYPE_COUNT 7
#define T_TYPE_NONE 0
#define T_TYPE_ATTENDANCE 1
#define T_TYPE_CHORE 2
#define T_TYPE_EXAM 3
#define T_TYPE_HW 4
#define T_TYPE_QUIZ 5
#define T_TYPE_READING 6
#define T_TYPE_PRESENTATION 7

#include "util/chrono.h"
#include "util/error.h"

typedef struct Task Task;
struct Task {
    Error (*destroy)(Task* self);
    Date dueDate;
    const char* name;
    int type;
};

typedef struct {
    Task base;
    int grade;
} AttendanceTask;

typedef struct {
    Task base;
} ChoreTask;

typedef struct {
    Task base;
    int grade;
} ExamTask;

typedef struct {
    Task base;
    int grade;
} HomeworkTask;

typedef struct {
    Task base;
    int grade;
} QuizTask;

typedef struct {
    Task base;
    int grade;
} ReadingTask;

typedef struct {
    Task base;
    int grade;
} PresentationTask;

Error destroyTask(Task* self);

AttendanceTask* createAttendanceTask(const char* n, Date d);
Error destroyAttendanceTask(Task* self);

ChoreTask* createChoreTask(const char* n, Date d);
Error destroyChoreTask(Task* self);

ExamTask* createExamTask(const char* n, Date d);
Error destroyExamTask(Task* self);

HomeworkTask* createHomeworkTask(const char* n, Date d);
Error destroyHomeworkTask(Task* self);

QuizTask* createQuizTask(const char* n, Date d);
Error destroyQuizTask(Task* self);

ReadingTask* createReadingTask(const char* n, Date d);
Error destroyReadingTask(Task* self);

PresentationTask* createPresentationTask(const char* n, Date d);
Error destroyPresentationTask(Task* self);

#endif
