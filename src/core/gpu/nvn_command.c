#include "nvn_command.h"
#include "vulkan_backend.h"
#include "vulkan_nvn_bridge.h"
#include "log.h"
#include <string.h>

static vulkan_nvn_bridge_t nvn_bridge = {0};

bool nvn_command_queue_init(nvn_command_queue_t *q) {
    if (!q) return false;
    memset(q, 0, sizeof(*q));
    return true;
}

void nvn_command_queue_destroy(nvn_command_queue_t *q) {
    if (!q) return;
    memset(q, 0, sizeof(*q));
}

bool nvn_command_queue_enqueue(nvn_command_queue_t *q, const nvn_command_t *cmd) {
    if (!q || !cmd) return false;
    if (q->count >= 256) return false;
    q->buf[q->tail] = *cmd;
    q->tail = (q->tail + 1) % 256;
    q->count++;
    return true;
}

bool nvn_command_queue_dequeue(nvn_command_queue_t *q, nvn_command_t *out) {
    if (!q || !out || q->count == 0) return false;
    *out = q->buf[q->head];
    q->head = (q->head + 1) % 256;
    q->count--;
    return true;
}

bool nvn_parse_command(uint64_t raw, nvn_command_t *out) {
    if (!out) return false;
    out->opcode = (uint32_t)(raw & 0xFF);
    out->size = (uint32_t)((raw >> 8) & 0xFFFFFF);
    out->flags = (raw >> 32) & 0xFFFFFFFF;
    out->data = 0;
    return true;
}

bool nvn_submit_command_buffer(nvn_command_t *cmd) {
    if (!cmd) return false;
    if (!nvn_bridge.initialized) {
        vulkan_nvn_bridge_init(&nvn_bridge);
    }
    POUND_LOG_INFO(&thread_logger, "NVN submit opcode %u size %u flags 0x%lx", cmd->opcode, cmd->size, cmd->flags);
    switch (cmd->opcode) {
        case 0x01:
            POUND_LOG_INFO(&thread_logger, "NVN Submit command buffer");
            vulkan_nvn_bridge_submit(&nvn_bridge, cmd->data, 1);
            break;
        case 0x02:
            POUND_LOG_INFO(&thread_logger, "NVN Set pipeline state");
            break;
        case 0x03:
            POUND_LOG_INFO(&thread_logger, "NVN Draw call");
            vk_submit_draw_call(0, cmd->size);
            vulkan_nvn_bridge_submit(&nvn_bridge, cmd->data, 1);
            break;
        default:
            POUND_LOG_WARN(&thread_logger, "NVN Unknown opcode %u", cmd->opcode);
            break;
    }
    return true;
}
