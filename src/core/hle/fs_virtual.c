#include "fs_virtual.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FS_ROOT "/tmp/pound_fs"
#define SAVE_DIR FS_ROOT "/save"
#define ROM_DIR  FS_ROOT "/rom"
#define SDMC_DIR FS_ROOT "/sdmc"

static void ensure_dirs(void) {
    system("mkdir -p " SAVE_DIR " " ROM_DIR " " SDMC_DIR);
}

int fs_virtual_init(void) {
    ensure_dirs();
    POUND_LOG_INFO(&hle_logger, "FS virtual init with save:/ rom:/ sdmc:/");
    return 0;
}

static const char* map_path(const char *path) {
    if (strncmp(path, "save:/", 6) == 0) {
        static char buf[512];
        snprintf(buf, sizeof(buf), "%s/%s", SAVE_DIR, path+6);
        return buf;
    }
    if (strncmp(path, "rom:/", 5) == 0) {
        static char buf[512];
        snprintf(buf, sizeof(buf), "%s/%s", ROM_DIR, path+5);
        return buf;
    }
    if (strncmp(path, "sdmc:/", 6) == 0) {
        static char buf[512];
        snprintf(buf, sizeof(buf), "%s/%s", SDMC_DIR, path+6);
        return buf;
    }
    return path;
}

int fs_open(const char *path, uint32_t flags, fs_handle_t **out) {
    if (!path || !out) return -1;
    const char *real = map_path(path);
    fs_handle_t *h = calloc(1, sizeof(fs_handle_t));
    if (!h) return -1;
    strncpy(h->path, real, sizeof(h->path)-1);
    h->open = true;
    *out = h;
    POUND_LOG_INFO(&hle_logger, "FS open %s -> %s", path, real);
    return 0;
}

int fs_read(fs_handle_t *h, void *buf, uint32_t size, uint32_t *out_read) {
    if (!h || !h->open) return -1;
    *out_read = 0;
    return 0;
}

int fs_write(fs_handle_t *h, const void *buf, uint32_t size, uint32_t *out_written) {
    if (!h || !h->open) return -1;
    *out_written = size;
    return 0;
}

int fs_close(fs_handle_t *h) {
    if (!h) return -1;
    h->open = false;
    free(h);
    return 0;
}
