#pragma once
#include <stdint.h>
#include <stdbool.h>

bool svc_open_file(const char *path, uint32_t mode);
bool svc_read_file(int fd, void *buf, size_t size, size_t *out_read);
bool svc_write_file(int fd, const void *buf, size_t size, size_t *out_written);
bool svc_close_file(int fd);
