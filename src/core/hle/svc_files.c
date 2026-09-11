#include "svc_files.h"
#include "log.h"
#include "fs_virtual.h"

static int next_fd = 3;

bool svc_open_file(const char *path, uint32_t mode) {
    fs_handle_t *h = NULL;
    if (fs_open(path, mode, &h) == 0) {
        POUND_LOG_INFO(&thread_logger, "svcOpenFile path=%s mode=%u fd=%d", path ? path : "null", mode, next_fd);
        next_fd++;
        return true;
    }
    return false;
}
    POUND_LOG_INFO(&thread_logger, "svcOpenFile path=%s mode=%u", path ? path : "null", mode);
    return true;
}
bool svc_read_file(int fd, void *buf, size_t size, size_t *out_read) {
    POUND_LOG_INFO(&thread_logger, "svcReadFile fd=%d size=%zu [virtual]", fd, size);
    if (out_read) *out_read = 0;
    return true;
}
bool svc_write_file(int fd, const void *buf, size_t size, size_t *out_written) {
    POUND_LOG_INFO(&thread_logger, "svcWriteFile fd=%d size=%zu [virtual]", fd, size);
    if (out_written) *out_written = 0;
    return true;
}
bool svc_close_file(int fd) {
    POUND_LOG_INFO(&thread_logger, "svcCloseFile fd=%d [virtual]", fd);
    return true;
}
