#include "syscalls.h"
#include "log.h"

bool svc_create_thread(uint64_t *args, uint64_t *ret) {
    if (!args || !ret) return false;
    uint64_t entry = args[0];
    uint64_t stack = args[1];
    uint64_t priority = args[2];
    POUND_LOG_INFO(&hle_logger, "svcCreateThread entry 0x%llX stack 0x%llX prio %llu", entry, stack, priority);
    *ret = 0;
    return true;
}

bool svc_start_thread(uint64_t *args, uint64_t *ret) {
    if (!args || !ret) return false;
    uint64_t handle = args[0];
    POUND_LOG_INFO(&hle_logger, "svcStartThread handle %llu", handle);
    *ret = 0;
    return true;
}
