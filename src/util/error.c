/**
 * @file error.c
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for error handling.
 */

#include "util/error.h"

#include <stdio.h>

/**
 * @author DargoDargonyx
 * @date 03/27/2026
 * @brief Creates a new Error strcut.
 *
 * @param statusNum : integer
 * @param msg : c-style string
 * @return The new Error struct
 */
Error createError(int statusNum, const char* msg) {
    Error err;
    err.statusNum = statusNum;
    err.msg = msg;
    return err;
}

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Gets a quick description of an error.
 *
 * This function gets a quick description of an error
 * when given an Error struct depending on the status
 * number relating to the error.
 *
 * @note Status numbers are defined in the header file.
 * @param err : Error struct pointer
 * @return The description of the error as a string pointer
 */
char* getErrorStatusDesc(Error* err) {
    static char str[63];

    switch (err->statusNum) {
		// error and main
		case ESTAT_MAIN_NONE:
			sprintf(str, "Null Status");
			break;
		case ESTAT_MAIN_LOAD:
			sprintf(str, "Loading Main File Error");
			break;
		// chrono
		case ESTAT_DATE_CREATE:
			sprintf(str, "Date Creation Error");
			break;
		case ESTAT_TIME_CREATE:
			sprintf(str, "Time Creation Error");
			break;
		// cli
		case ESTAT_CLI_FLAG_CREATE:
			sprintf(str, "CLI Flag Creation Error");
			break;
		case ESTAT_CLI_FLAG_DESTROY:
			sprintf(str, "CLI Flag Destruction Error");
			break;
		case ESTAT_CLI_OPT_CREATE:
			sprintf(str, "CLI Option Creation Error");
			break;
		case ESTAT_CLI_OPT_DESTROY:
			sprintf(str, "CLI Option Destruction Error");
			break;
		case ESTAT_CLI_CMD_CREATE:
			sprintf(str, "CLI Command Creation Error");
			break;
		case ESTAT_CLI_CMD_DESTROY:
			sprintf(str, "CLI Command Destruction Error");
			break;
		case ESTAT_CLI_CMD_TRACKER_CREATE:
			sprintf(str, "CLI Command Tracker Creation Error");
			break;
		case ESTAT_CLI_CMD_TRACKER_DESTROY:
			sprintf(str, "CLI Command Tracker Destruction Error");
			break;
		case ESTAT_CLI_CMD_TRACKER_ADD_CMD:
			sprintf(str, "CLI Command Tracker Command Adding Error");
			break;
		case ESTAT_CLI_CMD_TRACKER_ADD_ERR:
			sprintf(str, "CLI Command Tracker Error Adding Error");
			break;
		// config
		case ESTAT_CONFIG_LOAD:
			sprintf(str, "Configuration Data Loading Error");
			break;
		case ESTAT_CONFIG_SAVE:
			sprintf(str, "Configuration Data Saving Error");
			break;
		// data
		case ESTAT_DATA_MANAGER_CREATE:
			sprintf(str, "Data Manager Creation Error");
			break;
		case ESTAT_DATA_MANAGER_DESTROY:
			sprintf(str, "Data Manager Destruction Error");
			break;
		case ESTAT_DATA_MANAGER_ADD_ERR:
			sprintf(str, "Data Management Error Adding Error");
			break;
		// group
		case ESTAT_GROUP_CREATE:
			sprintf(str, "Group Creation Error");
			break;
		case ESTAT_GROUP_DESTROY:
			sprintf(str, "Group Destruction Error");
			break;
		case ESTAT_GROUP_CONTAINER_CREATE:
			sprintf(str, "Group Container Creation Error");
			break;
		case ESTAT_GROUP_CONTAINER_DESTROY:
			sprintf(str, "Group Container Destruction Error");
			break;
		case ESTAT_GROUP_ADD_TASK:
			sprintf(str, "Group Task Addition Error");
			break;
		case ESTAT_GROUP_CONTAINER_ADD_GROUP:
			sprintf(str, "Group Container Group Addition Error");
			break;
		// data
		case ESTAT_DATA_LOAD:
			sprintf(str, "Database Loading Error");
			break;
		case ESTAT_DATA_SAVE:
			sprintf(str, "Database Saving Error");
			break;
		// task
		case ESTAT_TASK_CREATE:
			sprintf(str, "Task Creation Error");
			break;
		case ESTAT_TASK_DESTROY:
			sprintf(str, "Task Destruction Error");
			break;
		default:
			sprintf(str, "Unknown Status");
			break;
    }

    return str;
}
