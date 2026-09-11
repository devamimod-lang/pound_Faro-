#pragma once
#include <stdint.h>
#include <stdbool.h>

#define FS_VIRTUAL_BASE "/tmp/pound_fs"

typedef struct {
    char path[256];
    bool open;
} fs_handle_t;

int fs_virtual_init(void);
int fs_open(const char *path, uint32_t flags, fs_handle_t **out);
int fs_read(fs_handle_t *h, void *buf, uint32_t size, uint32_t *out_read);
int fs_write(fs_handle_t *h, const void *buf, uint32_t size, uint32_t *out_written);
int fs_close(fs_handle_t *h);
