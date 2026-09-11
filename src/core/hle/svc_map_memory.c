#include "syscalls.h"
#include "log.h"

bool svc_map_memory(uint64_t *args, uint64_t *ret) {
    if (!args || !ret) return false;
    uint64_t addr = args[0];
    uint64_t size = args[1];
    uint64_t perm = args[2];
    POUND_LOG_INFO(&hle_logger, "svcMapMemory addr 0x%llX size %llu perm %llu", addr, size, perm);
    *ret = 0;
    return true;
}

bool svc_read_write_register(uint64_t *args, uint64_t *ret) {
    if (!args || !ret) return false;
    uint64_t reg = args[0];
    uint64_t value = args[1];
    POUND_LOG_INFO(&hle_logger, "svcReadWriteRegister reg %llu value 0x%llX", reg, value);
    *ret = 0;
    return true;
}

bool svc_sleep_thread(uint64_t *args, uint64_t *ret) {
    if (!args || !ret) return false;
    uint64_t ns = args[0];
    POUND_LOG_INFO(&hle_logger, "svcSleepThread %llu ns", ns);
    *ret = 0;
    return true;
}
