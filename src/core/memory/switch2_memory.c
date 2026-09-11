#include "switch2_memory.h"
#include "log.h"
#include "../gpu/nvn_mmio.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool switch2_memory_init(switch2_memory_t *mem, size_t ram_size) {
    if (!mem) return false;
    mem->ram_size = ram_size ? ram_size : 64*1024*1024;
    mem->ram = calloc(1, mem->ram_size);
    mem->kernel_size = 16*1024*1024;
    mem->kernel = calloc(1, mem->kernel_size);
    if (!mem->ram || !mem->kernel) return false;
    POUND_LOG_INFO(&mem_logger, "Switch2 memory init RAM %zu", mem->ram_size);
    return true;
}
void switch2_memory_destroy(switch2_memory_t *mem) {
    if (!mem) return;
    free(mem->ram);
    free(mem->kernel);
}
mem_region_t switch2_memory_region(uint64_t addr, size_t size) { return MEM_RAM; }
void* switch2_memory_translate(switch2_memory_t *mem, uint64_t addr) { return NULL; }
bool switch2_memory_write(switch2_memory_t *mem, uint64_t addr, const void *in, size_t size) {
    if (addr >= 0x10000000 && addr < 0x10010000) {
        uint64_t v = 0; memcpy(&v, in, size<8?size:8);
        nvn_mmio_ctx_t mm; nvn_mmio_init(&mm); nvn_mmio_write(&mm, addr, v, size); return true;
    }
    return true;
}
bool switch2_memory_read(switch2_memory_t *mem, uint64_t addr, void *out, size_t size) {
    memset(out,0,size); return true;
}
