/**
 * @file cli.h
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for command-line interfacing.
 */

#ifndef CLI_H
#define CLI_H

// Values

#define CLI_VAL_NULL 0
#define CLI_VAL_INT 1
#define CLI_VAL_STR 2

typedef struct {
    int type;
} CLI_Val;

typedef struct {
    CLI_Val base;
    int val;
} CLI_Int;

typedef struct {
    CLI_Val base;
    const char* val;
} CLI_Str;

CLI_Int CLI_createInt(int val);
CLI_Str CLI_createStr(const char* val);

// Flags, Opts, and Commands

#define CLI_TRACKER_CMDS_INIT_CAP 63
#define CLI_TRACKER_ERRS_INIT_CAP 15

#include "util/error.h"

typedef struct {
    const char* name;
    char mark;
    int val;
} CLI_Flag;

typedef struct {
    const char* name;
    char mark;
    const char* extMark;
    CLI_Val val;
} CLI_Opt;

typedef struct {
    const char* name;
    const char* desc;
    int flagCount;
    CLI_Flag** flags;
    int optCount;
    CLI_Opt** opts;
} CLI_CMD;

typedef struct {
    int cmdCount;
    int cmdCap;
    CLI_CMD** cmds;
    int errCount;
    int errCap;
    Error* errs;
} CLI_CMDTracker;

CLI_Flag* CLI_createFlag(const char* n, char m);
void CLI_destroyFlag(CLI_Flag* self);

CLI_Opt* CLI_createOpt(const char* n, char m, const char* em);
void CLI_destroyOpt(CLI_Opt* self);

void CLI_createCommand(CLI_CMDTracker* tracker, const char* n, const char* d,
                       int fc, CLI_Flag** f, int oc, CLI_Opt** o);
void CLI_destroyCommand(CLI_CMD* self);

CLI_CMDTracker CLI_createCommandTracker();
void CLI_destroyCommandTracker(CLI_CMDTracker* self);
void CLI_addCommand(CLI_CMDTracker* tracker, CLI_CMD* cmd);
void CLI_addError(CLI_CMDTracker* tracker, Error err);

#endif
