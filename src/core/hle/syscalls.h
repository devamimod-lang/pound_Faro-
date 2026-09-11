#pragma once
#include "pound_switch2.h"
#include <stdint.h>

typedef struct {
    pound_switch2_ctx_t *ctx;
} hle_context_t;

void hle_init(hle_context_t *hle, pound_switch2_ctx_t *ctx);
void hle_handle_syscall(hle_context_t *hle, uint32_t syscall_id, uint64_t *args, uint64_t *out);
