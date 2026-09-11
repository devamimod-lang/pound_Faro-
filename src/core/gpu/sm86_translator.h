#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    bool initialized;
} sm86_context_t;

bool sm86_init(sm86_context_t *ctx);
void sm86_destroy(sm86_context_t *ctx);
bool sm86_translate_shader(const void *sm86_code, size_t size, uint8_t **spirv_out, size_t *spirv_size);
