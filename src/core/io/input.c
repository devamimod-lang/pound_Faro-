#include "input.h"
#include "log.h"
#include <string.h>

bool input_init(input_ctx_t *ctx) {
    if (!ctx) return false;
    memset(ctx, 0, sizeof(*ctx));
    ctx->initialized = true;
    POUND_LOG_INFO(&io_logger, "Input init stub");
    return true;
}
void input_poll(input_ctx_t *ctx) {
    if (!ctx || !ctx->initialized) return;
}
