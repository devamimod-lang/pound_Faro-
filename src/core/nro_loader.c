#include "nro_loader.h"
#include "log.h"
#include "memory/switch2_memory.h"
#include <string.h>
#include <stdlib.h>

bool nro_loader_init(nro_loader_t *loader) {
    if (!loader) return false;
    memset(loader, 0, sizeof(*loader));
    loader->base_addr = 0x80010000ULL;
    POUND_LOG_INFO(&loader_logger, "NRO loader init base 0x%llX", loader->base_addr);
    return true;
}

bool nro_loader_load(nro_loader_t *loader, const uint8_t *data, size_t size) {
    if (!loader || !data || size < 0x200) return false;
    // Minimal NRO header check
    if (data[0] != 'N' || data[1] != 'R' || data[2] != 'O') {
        POUND_LOG_WARN(&loader_logger, "NRO magic mismatch");
    }
    if (!switch2_memory_write(loader->base_addr, data, size)) {
        return false;
    }
    loader->loaded_size = size;
    POUND_LOG_INFO(&loader_logger, "NRO loaded %zu bytes at 0x%llX", size, loader->base_addr);
    return true;
}

uint64_t nro_loader_entry(nro_loader_t *loader) {
    if (!loader) return 0;
    return loader->base_addr + 0x1000;
}
