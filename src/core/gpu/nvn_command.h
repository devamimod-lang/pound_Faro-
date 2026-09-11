#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t opcode;
    uint32_t size;
    uint64_t flags;
    uint64_t data;
} nvn_command_t;

typedef struct {
    nvn_command_t buf[256];
    int head;
    int tail;
    int count;
} nvn_command_queue_t;

bool nvn_command_queue_init(nvn_command_queue_t *q);
void nvn_command_queue_destroy(nvn_command_queue_t *q);
bool nvn_command_queue_enqueue(nvn_command_queue_t *q, const nvn_command_t *cmd);
bool nvn_command_queue_dequeue(nvn_command_queue_t *q, nvn_command_t *out);

bool nvn_parse_command(uint64_t raw, nvn_command_t *out);
bool nvn_submit_command_buffer(nvn_command_t *cmd);
