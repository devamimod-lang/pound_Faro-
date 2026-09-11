#include "core/memory/switch2_memory.h"
#include "core/gpu/nvn_mmio.h"
#include <stdio.h>
int main(void){
    switch2_memory_t mem;
    switch2_memory_init(&mem, 64*1024*1024);
    printf("Memory init OK\n");
    nvn_mmio_ctx_t mmio; 
    nvn_mmio_init(&mmio);
    nvn_mmio_write(&mmio,0x10004000,0x03,8);
    printf("NVN MMIO write OK\n");
    return 0;
}
