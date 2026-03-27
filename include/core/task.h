/**
 * @file task.h
 * @author DargoDargonyx
 * @date 03/27/2026
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

typedef struct Task Task;
struct Task {
    void (*destroy)(Task* self);
    const char* name;
    int type;
    Date dueDate;
};

typedef struct {
    Task base;
    int grade;
} Attendance;

typedef struct {
    Task base;
} Chore;

typedef struct {
    Task base;
    int grade;
} Exam;

typedef struct {
    Task base;
    int grade;
} Homework;

typedef struct {
    Task base;
    int grade;
} Quiz;

typedef struct {
    Task base;
    int grade;
} Reading;

typedef struct {
    Task base;
    int grade;
} Presentation;

#endif
