#include "switch2_memory_mmio.h"
#include "switch2_memory.h"
#include "log.h"

bool switch2_memory_init_mmio(switch2_memory_t *mem, nvn_mmio_ctx_t *nvn) {
    (void)mem; (void)nvn;
    return true;
}

bool switch2_memory_write_mmio(switch2_memory_t *mem, nvn_mmio_ctx_t *nvn, uint64_t addr, const void *in, size_t size) {
    mem_region_t region = switch2_memory_region(addr, size);
    if (region == MEM_MMIO) {
        // Dispatch to NVN
        const uint8_t *p = (const uint8_t *)in;
        for (size_t i = 0; i < size; i += 8) {
            uint64_t val = 0;
            size_t chunk = size - i < 8 ? size - i : 8;
            memcpy(&val, p + i, chunk);
            nvn_mmio_write(nvn, addr + i, val, chunk);
        }
        return true;
    }
    return switch2_memory_write(mem, addr, in, size);
}
