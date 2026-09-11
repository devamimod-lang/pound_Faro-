#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define SWITCH2_RAM_BASE   0x80000000ULL
#define SWITCH2_RAM_SIZE   (12ULL * 1024 * 1024 * 1024)
#define SWITCH2_KERNEL_BASE 0x40000000ULL
#define SWITCH2_KERNEL_SIZE (256ULL * 1024 * 1024)
#define SWITCH2_MMIO_BASE  0x10000000ULL
#define SWITCH2_MMIO_SIZE  (0x10000000ULL)

typedef enum {
    MEM_RAM,
    MEM_KERNEL,
    MEM_MMIO,
    MEM_UNMAPPED
} mem_region_t;

typedef struct {
    uint8_t *ram;
    size_t ram_size;
    uint8_t *kernel;
    size_t kernel_size;
} switch2_memory_t;

bool switch2_memory_init(switch2_memory_t *mem, size_t ram_size);
void switch2_memory_destroy(switch2_memory_t *mem);
mem_region_t switch2_memory_region(uint64_t addr, size_t size);
void* switch2_memory_translate(switch2_memory_t *mem, uint64_t addr);
bool switch2_memory_read(switch2_memory_t *mem, uint64_t addr, void *out, size_t size);
bool switch2_memory_write(switch2_memory_t *mem, uint64_t addr, const void *in, size_t size);
