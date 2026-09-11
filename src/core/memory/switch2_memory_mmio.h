#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "../gpu/nvn_mmio.h"

bool switch2_memory_init_mmio(switch2_memory_t *mem, nvn_mmio_ctx_t *nvn);
bool switch2_memory_write_mmio(switch2_memory_t *mem, nvn_mmio_ctx_t *nvn, uint64_t addr, const void *in, size_t size);
