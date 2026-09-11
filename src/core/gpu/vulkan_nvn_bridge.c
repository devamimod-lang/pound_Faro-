#include "vulkan_nvn_bridge.h"
#include "log.h"
#include <stdio.h>

int vulkan_nvn_bridge_init(vulkan_nvn_bridge_t *b) {
    if (!b) return -1;
    b->initialized = true;
    b->cmd_count = 0;
    POUND_LOG_INFO(&gpu_logger, "Vulkan NVN bridge init");
    return 0;
}

int vulkan_nvn_bridge_submit(vulkan_nvn_bridge_t *b, uint64_t cmd_buffer_addr, uint32_t count) {
    if (!b || !b->initialized) return -1;
    b->cmd_buffer_addr = cmd_buffer_addr;
    b->cmd_count = count;
    POUND_LOG_INFO(&gpu_logger, "Vulkan NVN submit cmd_buffer=0x%016llx count=%u", (unsigned long long)cmd_buffer_addr, count);
    return 0;
}

int vulkan_nvn_bridge_destroy(vulkan_nvn_bridge_t *b) {
    if (!b) return -1;
    b->initialized = false;
    POUND_LOG_INFO(&gpu_logger, "Vulkan NVN bridge destroy");
    return 0;
}
