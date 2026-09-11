#include "nvn_mmio.h"
#include "nvn_command.h"
#include "vulkan_nvn_bridge.h"
#include "log.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define NVN_MMIO_BASE 0x10000000ULL
#define NVN_CMD_SUBMIT_OFFSET 0x00004000ULL
#define NVN_CMD_SUBMIT_SIZE   0x1000ULL
#define SM86_SPECIFIC_OFFSET  0x00008000ULL

typedef struct {
    bool initialized;
    uint64_t base;
    nvn_command_queue_t cmd_queue;
    vulkan_nvn_bridge_t vk_bridge;
} nvn_mmio_ctx_impl_t;

bool nvn_mmio_init(nvn_mmio_ctx_t *ctx) {
    if (!ctx) return false;
    nvn_mmio_ctx_impl_t *impl = (nvn_mmio_ctx_impl_t *)ctx;
    memset(impl, 0, sizeof(*impl));
    impl->base = NVN_MMIO_BASE;
    impl->initialized = true;
    if (!nvn_command_queue_init(&impl->cmd_queue)) {
        POUND_LOG_ERROR(&gpu_logger, "nvn command queue init failed");
        return false;
    }
    if (!vulkan_nvn_bridge_init(&impl->vk_bridge)) {
        POUND_LOG_WARN(&gpu_logger, "vulkan bridge init failed, using stub");
    }
    POUND_LOG_INFO(&gpu_logger, "NVN MMIO init base 0x%016llX", impl->base);
    return true;
}

void nvn_mmio_destroy(nvn_mmio_ctx_t *ctx) {
    if (!ctx) return;
    nvn_mmio_ctx_impl_t *impl = (nvn_mmio_ctx_impl_t *)ctx;
    vulkan_nvn_bridge_destroy(&impl->vk_bridge);
    nvn_command_queue_destroy(&impl->cmd_queue);
    impl->initialized = false;
}

static bool handle_command_submit(nvn_mmio_ctx_impl_t *impl, uint64_t offset, uint64_t value) {
    if (offset >= NVN_CMD_SUBMIT_OFFSET && offset < NVN_CMD_SUBMIT_OFFSET + NVN_CMD_SUBMIT_SIZE) {
        POUND_LOG_INFO(&gpu_logger, "NVN command submit write offset 0x%llX value 0x%llX", offset, value);
        nvn_command_t cmd;
        cmd.opcode = (uint8_t)(value & 0xFF);
        cmd.size = (uint32_t)((value >> 8) & 0xFFFFFF);
        cmd.flags = value >> 32;
        cmd.data = 0;
        if (!nvn_command_queue_enqueue(&impl->cmd_queue, &cmd)) {
            POUND_LOG_ERROR(&gpu_logger, "Failed to enqueue NVN command");
            return false;
        }
        vulkan_nvn_bridge_submit(&impl->vk_bridge, cmd.data, 1);
        return true;
    }
    return false;
}

bool nvn_mmio_write(nvn_mmio_ctx_t *ctx, uint64_t addr, uint64_t value, size_t size) {
    if (!ctx) return false;
    nvn_mmio_ctx_impl_t *impl = (nvn_mmio_ctx_impl_t *)ctx;
    if (!impl->initialized) return false;
    if (addr < impl->base) {
        POUND_LOG_WARN(&gpu_logger, "NVN MMIO write to non-MMIO addr 0x%llX", addr);
        return false;
    }
    uint64_t offset = addr - impl->base;
    POUND_LOG_DEBUG(&gpu_logger, "NVN MMIO write base 0x%llX offset 0x%llX value 0x%llX size %zu", impl->base, offset, value, size);
    if (handle_command_submit(impl, offset, value)) return true;
    if (offset >= SM86_SPECIFIC_OFFSET) {
        POUND_LOG_INFO(&gpu_logger, "SM86 specific register write offset 0x%llX", offset);
        return true;
    }
    POUND_LOG_DEBUG(&gpu_logger, "NVN MMIO write to unhandled region offset 0x%llX", offset);
    return true;
}

uint64_t nvn_mmio_read(nvn_mmio_ctx_t *ctx, uint64_t addr, size_t size) {
    if (!ctx) return 0;
    nvn_mmio_ctx_impl_t *impl = (nvn_mmio_ctx_impl_t *)ctx;
    if (!impl->initialized) return 0;
    if (addr < impl->base) return 0;
    uint64_t offset = addr - impl->base;
    POUND_LOG_DEBUG(&gpu_logger, "NVN MMIO read base 0x%llX offset 0x%llX size %zu", impl->base, offset, size);
    return 0;
}
