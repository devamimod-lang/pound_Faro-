#include "../src/core/pound_switch2.h"
#include <stdio.h>
#include <stdint.h>

int main(void) {
    pound_switch2_ctx_t ctx = {0};
    if (!pound_switch2_init(&ctx, 64*1024*1024)) {
        printf("init failed\n");
        return 1;
    }
    uint32_t code[] = {
        0xD2800054, // MOVZ X0, #42
        0xD65F03C0  // RET
    };
    uint64_t load_addr = 0x80000000ULL;
    if (!pound_switch2_load_bin(&ctx, code, sizeof(code), load_addr)) {
        printf("load failed\n");
        pound_switch2_destroy(&ctx);
        return 2;
    }
    pound_switch2_set_pc(&ctx, load_addr);
    if (!pound_switch2_run(&ctx)) {
        printf("run failed\n");
        pound_switch2_destroy(&ctx);
        return 3;
    }
    printf("x0 = %llu\n", (unsigned long long)ctx.cpu.x[0]);
    pound_switch2_destroy(&ctx);
    return ctx.cpu.x[0] == 42 ? 0 : 4;
}
