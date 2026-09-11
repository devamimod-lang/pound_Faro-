#include "pound_switch2.h"
#include "log.h"
#include "guest_state.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

static void *ballistic_alloc(void *ctx, size_t alignment, size_t size)
{
    (void)ctx;
    void *p = NULL;
    if (posix_memalign(&p, alignment ? alignment : 64, size) != 0) return NULL;
    return p;
}
static void ballistic_free(void *ctx, void *ptr, size_t size) { (void)ctx; (void)size; free(ptr); }

bool pound_switch2_init(pound_switch2_ctx_t *ctx, size_t guest_memory_size)
{
    if (!ctx || guest_memory_size == 0) {
        POUND_LOG_ERROR(&thread_logger, "pound_switch2_init: invalid args");
        return false;
    }
    memset(ctx, 0, sizeof(*ctx));

    bal_logger_init_default();
    bal_allocator_default_init(&ctx->allocator);

    if (!switch2_memory_init(&ctx->mem, guest_memory_size ? guest_memory_size : SWITCH2_RAM_SIZE)) {
        POUND_LOG_ERROR(&thread_logger, "switch2_memory_init failed");
        return false;
    }
    ctx->guest_memory_size = ctx->mem.ram_size;

    bal_error_t err = bal_flat_translation_interface_init(&ctx->allocator, &ctx->memory, ctx->mem.ram, ctx->mem.ram_size);
    if (err != BAL_SUCCESS) {
        POUND_LOG_ERROR(&thread_logger, "bal_flat_translation_interface_init failed");
        switch2_memory_destroy(&ctx->mem);
        return false;
    }

    memset(&ctx->cpu, 0, sizeof(ctx->cpu));
    memset(&ctx->engine, 0, sizeof(ctx->engine));

    err = bal_engine_init(&ctx->engine, &ctx->cpu, &ctx->allocator, &ctx->memory);
    if (err != BAL_SUCCESS) {
        POUND_LOG_ERROR(&thread_logger, "bal_engine_init failed");
        bal_flat_translation_interface_destroy(&ctx->allocator, &ctx->memory);
        return false;
    }

    ctx->initialized = true;
    POUND_LOG_INFO(&thread_logger, "pound_switch2_init: Ballistic engine ready, guest memory %zu bytes", guest_memory_size);
    return true;
}

void pound_switch2_destroy(pound_switch2_ctx_t *ctx)
{
    if (!ctx || !ctx->initialized) return;
    bal_engine_destroy(&ctx->engine);
    bal_flat_translation_interface_destroy(&ctx->allocator, &ctx->memory);
    switch2_memory_destroy(&ctx->mem);
    ctx->initialized = false;
    POUND_LOG_INFO(&thread_logger, "pound_switch2_destroy");
}

bool pound_switch2_load_bin(pound_switch2_ctx_t *ctx, const void *data, size_t size, uint64_t load_addr)
{
    if (!ctx || !ctx->initialized || !data || size == 0) return false;
    if (!switch2_memory_write(&ctx->mem, load_addr, data, size)) {
        POUND_LOG_ERROR(&thread_logger, "load_bin out of bounds or unmapped");
        return false;
    }
    POUND_LOG_INFO(&thread_logger, "pound_switch2_load_bin: %zu bytes at 0x%lx", size, (unsigned long)load_addr);
    return true;
}

bool pound_switch2_run(pound_switch2_ctx_t *ctx)
{
    if (!ctx || !ctx->initialized) {
        POUND_LOG_ERROR(&thread_logger, "pound_switch2_run: not initialized");
        return false;
    }
    bal_error_t err = bal_engine_run_thread(&ctx->engine);
    if (err != BAL_SUCCESS) {
        POUND_LOG_ERROR(&thread_logger, "bal_engine_run_thread error %d", err);
        return false;
    }
    POUND_LOG_INFO(&thread_logger, "pound_switch2_run: execution finished, x0=%llu", (unsigned long long)ctx->cpu.x[0]);
    return true;
}

void pound_switch2_reset(pound_switch2_ctx_t *ctx)
{
    if (!ctx || !ctx->initialized) return;
    bal_engine_reset(&ctx->engine);
    memset(&ctx->cpu, 0, sizeof(ctx->cpu));
    POUND_LOG_INFO(&thread_logger, "pound_switch2_reset");
}

void pound_switch2_set_pc(pound_switch2_ctx_t *ctx, uint64_t pc)
{
    if (!ctx || !ctx->initialized) return;
    ctx->cpu.pc = pc;
}
