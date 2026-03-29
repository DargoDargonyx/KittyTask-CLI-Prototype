/**
 * @file main.c
 * @author DargoDargonyx
 * @date 03/27/2026
 * @brief The main file.
 */

#include "core/interactive.h"
#include "util/error.h"

#include <stdio.h>

#define PREAMBLE "[Kitty] "

/**
 * @author DargoDargonyx
 * @date 03/29/2026
 * @brief The main function for the app.
 *
 * @param argc : integer
 * @param argv : c-style array of c-style strings
 * @return Whether or not the app ran successfully
 */
int main(int argc, char** argv) {
    printf("Successfully started the main file.\n");
    Error err = createError(ESTAT_MAIN_NONE, NULL);

    if (argc == 1)
        err = startInteractiveLoop(PREAMBLE);

    if (err.statusNum != ESTAT_MAIN_NONE) {
        printf("%sERROR {%s} : %s.\n", PREAMBLE, getErrorStatusDesc(&err),
               err.msg);
        return 0;
    }

    return 0;
}
