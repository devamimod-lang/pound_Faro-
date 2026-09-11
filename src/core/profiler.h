#pragma once
#include <stdint.h>

typedef struct {
    uint64_t instructions_executed;
    uint64_t blocks_compiled;
} profiler_t;

void profiler_init(profiler_t *p);
void profiler_log(const profiler_t *p);
