/**
 * @file error.h
 * @author DargoDargonyx
 * @date 03/29/2026
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

// cli
#define ESTAT_CLI_FLAG_CREATE 0x20
#define ESTAT_CLI_FLAG_DESTROY 0x21
#define ESTAT_CLI_OPT_CREATE 0x22
#define ESTAT_CLI_OPT_DESTROY 0x23
#define ESTAT_CLI_CMD_CREATE 0x24
#define ESTAT_CLI_CMD_DESTROY 0x25
#define ESTAT_CLI_CMD_TRACKER_CREATE 0x26
#define ESTAT_CLI_CMD_TRACKER_DESTROY 0x27
#define ESTAT_CLI_CMD_TRACKER_ADD_CMD 0x28
#define ESTAT_CLI_CMD_TRACKER_ADD_ERR 0x29

// config
#define ESTAT_CONFIG_LOAD 0x30
#define ESTAT_CONFIG_SAVE 0x31

// data
#define ESTAT_DATA_MANAGER_CREATE 0x40
#define ESTAT_DATA_MANAGER_DESTROY 0x41
#define ESTAT_DATA_MANAGER_ADD_ERR 0x42

// group
#define ESTAT_GROUP_CREATE 0x50
#define ESTAT_GROUP_DESTROY 0x51

// data
#define ESTAT_DATA_LOAD 0x60
#define ESTAT_DATA_SAVE 0x61

// task
#define ESTAT_TASK_CREATE 0x70
#define ESTAT_TASK_DESTROY 0x71

typedef struct {
    int statusNum;
    const char* msg;
} Error;

Error createError(int statusNum, const char* msg);
char* getErrorStatusDesc(Error* err);

#endif
