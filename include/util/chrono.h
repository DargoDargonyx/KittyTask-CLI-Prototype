/**
 * @file chrono.h
 * @author DargoDargonyx
 * @date 03/27/2026
 * @brief Handles the logic for time handling.
 */

#ifndef DATE_H
#define DATE_H

#include <stdint.h>

typedef struct {
    uint16_t y;
    uint8_t m;
    uint8_t d;
} Date;

typedef struct {
    uint8_t h;
    uint8_t m;
    uint8_t s;
} Time;

#endif
