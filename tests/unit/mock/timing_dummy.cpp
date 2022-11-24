#include "timing.h"

#define TICKS_PERIOD 0x80000000

uint32_t ticks_ms() {
    return 0;
}

int32_t ticks_diff(uint32_t ticks_a, uint32_t ticks_b) {
    return ((int32_t)(((ticks_a - ticks_b + TICKS_PERIOD / 2) & (TICKS_PERIOD - 1)) - TICKS_PERIOD / 2));
}
