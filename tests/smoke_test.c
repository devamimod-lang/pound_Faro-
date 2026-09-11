#include "core/memory/switch2_memory.h"
#include "core/gpu/nvn_mmio.h"
#include "core/hle/syscalls.h"
#include <stdio.h>

int main(void) {
    if (!switch2_memory_init()) { printf("mem fail\n"); return 1; }
    nvn_mmio_ctx_t mmio;
    nvn_mmio_init(&mmio);
    uint64_t args[4]={0};
    uint64_t ret;
    hle_dispatch(0x0008, args, &ret);
    printf("Smoke test passed\n");
    nvn_mmio_destroy(&mmio);
    switch2_memory_destroy();
    return 0;
}
