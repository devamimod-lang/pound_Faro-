#include "audio.h"
#include "log.h"
#include <string.h>

bool audio_init(audio_ctx_t *ctx) {
    if (!ctx) return false;
    memset(ctx, 0, sizeof(*ctx));
    ctx->initialized = true;
    POUND_LOG_INFO(&audio_logger, "Audio init stub");
    return true;
}
void audio_submit(audio_ctx_t *ctx, const void *data, size_t size) {
    if (!ctx || !ctx->initialized) return;
}
