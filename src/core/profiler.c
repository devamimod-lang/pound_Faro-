#include "profiler.h"
#include "log.h"

void profiler_init(profiler_t *p) {
    p->instructions_executed = 0;
    p->blocks_compiled = 0;
}
void profiler_log(const profiler_t *p) {
    POUND_LOG_INFO(&thread_logger, "Profiler: instructions %llu blocks %llu", (unsigned long long)p->instructions_executed, (unsigned long long)p->blocks_compiled);
}
