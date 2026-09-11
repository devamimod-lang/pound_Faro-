#include "nro_relocations.h"
#include "log.h"
#include <string.h>

bool nro_apply_relocations(uint8_t *base, size_t size, const nro_reloc_t *rels, size_t rel_count, uint64_t load_addr) {
    if (!base || !rels) return false;
    for (size_t i = 0; i < rel_count; i++) {
        uint64_t off = rels[i].offset;
        if (off + 8 > size) {
            POUND_LOG_WARN(&thread_logger, "Reloc out of bounds");
            continue;
        }
        uint64_t val = 0;
        memcpy(&val, base + off, sizeof(val));
        uint64_t new_val = val + rels[i].addend + load_addr;
        memcpy(base + off, &new_val, sizeof(new_val));
        POUND_LOG_INFO(&thread_logger, "Reloc applied at 0x%lx", off);
    }
    return true;
}
