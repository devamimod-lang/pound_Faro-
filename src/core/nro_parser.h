#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "pound_switch2.h"

typedef struct {
    uint64_t vaddr;
    uint64_t size;
    uint8_t *data;
} nro_segment_t;

typedef struct {
    nro_segment_t text;
    nro_segment_t rodata;
    nro_segment_t data;
    nro_segment_t bss;
} nro_segments_t;

bool nro_parse_segments(const void *data, size_t size, nro_segments_t *out);
bool nro_load_segments(pound_switch2_ctx_t *ctx, const nro_segments_t *segs, uint64_t base);
