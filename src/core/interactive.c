/**
 * @file interactive.c
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for the interactive mode
 * for the app.
 */

#include "core/interactive.h"
#include "util/error.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief Handles the logic for starting the loop
 * for the interactive mode of the app.
 *
 * @param preamble : c-style string
 * @return An Error struct describing whether or not
 * an issue occured while the loop was being run.
 */
Error startInteractiveLoop(const char* preamble) {
    int running = 1;
    char* response = NULL;
    size_t len = 0;
    ssize_t read = 0;
    while (running) {
        printf("%sEnter something: ", preamble);
        read = getline(&response, &len, stdin);
        if (read == 2 && response[0] == 'q')
            running = 0;
        else
            printf("%sYou didn't enter \"q\".\n", preamble);
    }
    free(response);
    return createError(ESTAT_MAIN_NONE, NULL);
}
