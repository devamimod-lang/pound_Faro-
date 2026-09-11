#include "core/gpu/nvn_mmio.h"
#include <stdio.h>

int main(void) {
    nvn_mmio_ctx_t ctx;
    if (!nvn_mmio_init(&ctx)) {
        printf("init failed\n");
        return 1;
    }
    // Write to command submit region
    uint64_t addr = 0x10004000ULL;
    uint64_t value = 0x00000103ULL; // opcode 0x03 draw
    nvn_mmio_write(&ctx, addr, value, 8);
    printf("NVN MMIO stub test passed\n");
    nvn_mmio_destroy(&ctx);
    return 0;
}
