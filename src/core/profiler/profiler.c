#include "profiler.h"
#include "log.h"
#include <time.h>
#include <stdint.h>

static struct timespec start;

void profiler_start(void) {
    clock_gettime(CLOCK_MONOTONIC, &start);
    POUND_LOG_INFO(&prof_logger, "Profiler started");
}

void profiler_mark(const char *label) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    uint64_t elapsed = (now.tv_sec - start.tv_sec) * 1000000000ULL + (now.tv_nsec - start.tv_nsec);
    POUND_LOG_INFO(&prof_logger, "[%s] %llu ns", label, elapsed);
}
