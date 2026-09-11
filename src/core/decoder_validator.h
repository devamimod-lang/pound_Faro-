#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

bool decoder_validate_arm64_block(const uint8_t *code, size_t size);
