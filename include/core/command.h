/**
 * @file command.h
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for commands.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "util/error.h"
#include "core/group.h"
#include "core/task.h"
#include "core/cli.h"

// groups
Error listGroupsCMD(const char* preamble, CLI_CMD* cmd, GroupContainer* container);
Error addGroupCMD(const char* preamble, CLI_CMD* cmd, 
		GroupContainer* container, Group* group);
Error removeGroupCMD(const char* preamble, CLI_CMD* cmd);
Error countGroupsCMD(const char* preamble, CLI_CMD* cmd, GroupContainer* container);

// tasks
Error listTasksCMD(const char* preamble, CLI_CMD* cmd, Group* group);
Error addTaskCMD(const char* preamble, CLI_CMD* cmd, Group* group, Task* task);
Error removeTaskCMD(const char* preamble, CLI_CMD* cmd, const char* taskName);
Error countTasksCMD(const char* preamble, CLI_CMD* cmd, Group* group);

#endif
