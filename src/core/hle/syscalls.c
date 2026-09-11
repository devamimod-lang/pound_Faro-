#include "syscalls.h"
#include "log.h"
#include "svc_create_thread.c"
#include "svc_files.c"
#include "svc_map_memory.c"
#include <string.h>

bool hle_dispatch(uint32_t svc_id, uint64_t *args, uint64_t *ret) {
    switch (svc_id) {
        case 0x0000:
            *ret = 0; return true;
        case 0x0008:
            return svc_create_thread(args, ret);
        case 0x0009:
            return svc_start_thread(args, ret);
        case 0x0004:
            return svc_map_memory(args, ret);
        case 0x004E:
            return svc_read_write_register(args, ret);
        case 0x001F:
            return svc_sleep_thread(args, ret);
        case 0x0010:
            return svc_open_file(args, ret);
        case 0x0011:
            return svc_read_file(args, ret);
        case 0x0012:
            return svc_write_file(args, ret);
        case 0x0013:
            return svc_close_file(args, ret);
        default:
            POUND_LOG_WARN(&hle_logger, "Unhandled SVC 0x%04X", svc_id);
            *ret = 0;
            return true;
    }
}
