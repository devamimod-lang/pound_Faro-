#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint64_t cmd_buffer_addr;
    uint32_t cmd_count;
    bool initialized;
} vulkan_nvn_bridge_t;

int vulkan_nvn_bridge_init(vulkan_nvn_bridge_t *b);
int vulkan_nvn_bridge_submit(vulkan_nvn_bridge_t *b, uint64_t cmd_buffer_addr, uint32_t count);
int vulkan_nvn_bridge_destroy(vulkan_nvn_bridge_t *b);
