#include "nro_parser.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>

bool nro_parse_segments(const void *data, size_t size, nro_segments_t *out) {
    if (!data || !out || size < 0x100) return false;
    memset(out, 0, sizeof(*out));
    // Stub: assume segments at fixed offsets
    out->text.vaddr = 0x80010000;
    out->text.size = 0x10000;
    POUND_LOG_INFO(&thread_logger, "NRO parse stub");
    return true;
}

bool nro_load_segments(pound_switch2_ctx_t *ctx, const nro_segments_t *segs, uint64_t base) {
    if (!ctx || !segs) return false;
    // Stub load
    POUND_LOG_INFO(&thread_logger, "NRO load segments stub");
    return true;
}
