#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "../pound_switch2.h"

bool svc_map_memory(pound_switch2_ctx_t *ctx, uint64_t addr, uint64_t size, uint32_t perm);
