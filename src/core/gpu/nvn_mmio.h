#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    bool initialized;
    uint8_t data[16384];
} nvn_mmio_ctx_t;

bool nvn_mmio_init(nvn_mmio_ctx_t *ctx);
void nvn_mmio_destroy(nvn_mmio_ctx_t *ctx);
bool nvn_mmio_write(nvn_mmio_ctx_t *ctx, uint64_t addr, uint64_t value, size_t size);
uint64_t nvn_mmio_read(nvn_mmio_ctx_t *ctx, uint64_t addr, size_t size);
