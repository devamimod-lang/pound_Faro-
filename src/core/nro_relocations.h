#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint64_t offset;
    uint64_t addend;
    uint32_t type;
} nro_reloc_t;

bool nro_apply_relocations(uint8_t *base, size_t size, const nro_reloc_t *rels, size_t rel_count, uint64_t load_addr);
