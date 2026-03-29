/**
 * @file cli.c
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for command-line interfacing.
 */

#include "core/cli.h"
#include "util/error.h"

#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating a CLI_Int struct.
 *
 * @param val : integer
 * @return The CLI_Int struct
 */
CLI_Int CLI_createInt(int val) {
    CLI_Int i;
    i.base.type = CLI_VAL_INT;
    i.val = val;
    return i;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating a CLI_Str struct.
 *
 * @param val : c-style string
 * @return The CLI_Str struct
 */
CLI_Str CLI_createStr(const char* val) {
    CLI_Str s;
    s.base.type = CLI_VAL_STR;
    s.val = val;
    return s;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating a CLI_Flag struct.
 *
 * @param n : c-style string
 * @param m : char
 * @return A pointer to the CLI_Flag struct
 */
CLI_Flag* CLI_createFlag(const char* n, char m) {
    CLI_Flag* flag = (CLI_Flag*)malloc(sizeof(CLI_Flag));
    flag->name = n;
    flag->mark = m;
    flag->val = 0;

    return flag;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for destroying a CLI_Flag struct.
 *
 * @param self : CLI_Flag struct pointer
 */
void CLI_destroyFlag(CLI_Flag* self) { free(self); }

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating a CLI_Opt struct.
 *
 * @param n : c-style string
 * @param m : char
 * @param em : c-style string
 * @return A pointer to the CLI_Opt struct
 */
CLI_Opt* CLI_createOpt(const char* n, char m, const char* em) {
    CLI_Opt* opt = (CLI_Opt*)malloc(sizeof(CLI_Opt));
    opt->name = n;
    opt->mark = m;
    opt->extMark = em;
    opt->val = (CLI_Val){CLI_VAL_NULL};

    return opt;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for destroying a CLI_Opt struct.
 *
 * @param self : CLI_Opt struct pointer
 */
void CLI_destroyOpt(CLI_Opt* self) { free(self); }

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating a CLI_CMD struct.
 *
 * @param tracker : CLI_CMDTracker struct pointer
 * @param n : c-style string
 * @param d : c-style string
 * @param fc : integer
 * @param f : c-style array of CLI_Flag structs
 * @param oc : integer
 * @param o : c-style array of CLI_Opt structs
 */
void CLI_createCommand(CLI_CMDTracker* tracker, const char* n, const char* d,
                       int fc, CLI_Flag** f, int oc, CLI_Opt** o) {

    CLI_CMD* cmd = (CLI_CMD*)malloc(sizeof(CLI_CMD));
    cmd->name = n;
    cmd->desc = d;
    cmd->flagCount = fc;
    cmd->flags = f;
    cmd->optCount = oc;
    cmd->opts = o;
    CLI_addCommand(tracker, cmd);
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for destroying a CLI_CMD struct.
 *
 * @param self : CLI_CMD struct pointer
 */
void CLI_destroyCommand(CLI_CMD* self) {
    for (int i = 0; i < self->flagCount; i++) {
        CLI_destroyFlag(self->flags[i]);
    }
    free(self->flags);
    for (int i = 0; i < self->optCount; i++) {
        CLI_destroyOpt(self->opts[i]);
    }
    free(self->opts);
    free(self);
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for creating a CLI_CMDTracker struct.
 *
 * @return The CLI_CMDTracker struct
 */
CLI_CMDTracker CLI_createCommandTracker() {
    CLI_CMDTracker tracker;
    tracker.cmdCount = 0;
    tracker.cmdCap = CLI_TRACKER_CMDS_INIT_CAP;
    tracker.cmds = (CLI_CMD**)calloc(tracker.cmdCap, sizeof(CLI_CMD*));
    tracker.errCount = 0;
    tracker.errCap = CLI_TRACKER_ERRS_INIT_CAP;
    tracker.errs = (Error*)calloc(tracker.errCap, sizeof(Error));

    return tracker;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for destroying a CLI_CMDTracker struct.
 *
 * @param self : CLI_CMDTracker struct pointer
 */
void CLI_destroyCommandTracker(CLI_CMDTracker* self) {
    for (int i = 0; i < self->cmdCount; i++) {
        CLI_destroyCommand(self->cmds[i]);
    }
    free(self->cmds);
    free(self->errs);
    free(self);
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for adding a CLI_CMD struct to
 * a CLI_CMDTracker struct.
 *
 * @param tracker : CLI_CMDTracker struct pointer
 * @param cmd : CLI_CMD struct pointer
 */
void CLI_addCommand(CLI_CMDTracker* tracker, CLI_CMD* cmd) {
    if (tracker->cmdCount == tracker->cmdCap) {
        tracker->cmdCap = (tracker->cmdCount + 1) * 2;
        CLI_CMD** orig = tracker->cmds;
        CLI_CMD** temp = (CLI_CMD**)calloc(tracker->cmdCap, sizeof(CLI_CMD*));
        for (int i = 0; i < tracker->cmdCount; i++) {
            temp[i] = orig[i];
        }
        free(orig);
        tracker->cmds = temp;
    }

    tracker->cmds[tracker->cmdCount] = cmd;
    tracker->cmdCount++;
}

/**
 * @author DargoDargonyx
 * @date 03/28/2026
 * @brief Handles the logic for adding an Error struct to
 * a CLI_CMDTracker struct.
 *
 * @param tracker : CLI_CMDTracker struct pointer
 * @param err : Error struct
 */
void CLI_addError(CLI_CMDTracker* tracker, Error err) {
    if (tracker->errCount == tracker->errCap) {
        tracker->errCap = (tracker->errCount + 1) * 2;
        Error* orig = tracker->errs;
        Error* temp = (Error*)calloc(tracker->errCap, sizeof(Error));
        for (int i = 0; i < tracker->errCount; i++) {
            temp[i] = orig[i];
        }
        free(orig);
        tracker->errs = temp;
    }

    tracker->errs[tracker->errCount] = err;
    tracker->errCount++;
}
