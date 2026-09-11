#pragma once
// Pound Switch 2 integration for Ballistic JIT.
// Full Ballistic headers are included directly from extern/ballistic.

#include "guest_state.h"
#include "memory/switch2_memory.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "bal_engine.h"
#include "bal_memory.h"
#include "bal_log.h"
#include "backend/bal_cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    bal_engine_t          engine;
    bal_cpu_t             cpu;
    bal_allocator_t       allocator;
    bal_memory_interface_t memory;
    switch2_memory_t      mem;
    void                 *guest_memory;
    size_t                guest_memory_size;
    bool                  initialized;
} pound_switch2_ctx_t;

bool pound_switch2_init(pound_switch2_ctx_t *ctx, size_t guest_memory_size);
void pound_switch2_destroy(pound_switch2_ctx_t *ctx);
bool pound_switch2_load_bin(pound_switch2_ctx_t *ctx, const void *data, size_t size, uint64_t load_addr);
bool pound_switch2_run(pound_switch2_ctx_t *ctx);
void pound_switch2_reset(pound_switch2_ctx_t *ctx);
void pound_switch2_set_pc(pound_switch2_ctx_t *ctx, uint64_t pc);

#ifdef __cplusplus
}
#endif
