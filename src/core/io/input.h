#pragma once
#include <stdbool.h>

typedef struct {
    bool initialized;
} input_ctx_t;

bool input_init(input_ctx_t *ctx);
void input_update(input_ctx_t *ctx);
void input_destroy(input_ctx_t *ctx);
