/**
 * @file error.h
 * @author DargoDargonyx
 * @date 03/27/2026
 * @brief Handles the logic for error handling.
 */

#ifndef ERROR_H
#define ERROR_H

// error and main
#define ESTAT_MAIN_NONE 0x0
#define ESTAT_MAIN_LOAD 0x1

// chrono
#define ESTAT_DATE_CREATE 0x10
#define ESTAT_TIME_CREATE 0x11

// config
#define ESTAT_CONFIG_LOAD 0x20
#define ESTAT_CONFIG_SAVE 0x21

// group
#define ESTAT_GROUP_CREATE 0x30
#define ESTAT_GROUP_DESTROY 0x31

// data
#define ESTAT_DATA_LOAD 0x40
#define ESTAT_DATA_SAVE 0x41

// task
#define ESTAT_TASK_CREATE 0x50
#define ESTAT_TASK_DESTROY 0x51

typedef struct {
    int statusNum;
    const char* msg;
} Error;

Error createError(int statusNum, const char* msg);
char* getErrorStatusDesc(Error* err);

#endif
