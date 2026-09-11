#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "pound_switch2.h"

typedef struct {
    uint8_t magic[4];
    uint32_t version;
    uint32_t size;
    uint64_t entry_point;
    uint32_t num_segments;
    uint32_t num_imports;
} nro_header_t;

bool nro_load_from_file(pound_switch2_ctx_t *ctx, const char *path, uint64_t base_addr);
bool nro_load_from_memory(pound_switch2_ctx_t *ctx, const void *data, size_t size, uint64_t base_addr);
