#include "switch2_interrupts.h"
#include "log.h"
#include <stdbool.h>

static bool irq_pending[256] = {0};

bool switch2_interrupts_init(void) {
    for (int i=0;i<256;i++) irq_pending[i]=false;
    POUND_LOG_INFO(&mem_logger, "Interrupts init");
    return true;
}

void switch2_interrupts_destroy(void) {
    POUND_LOG_INFO(&mem_logger, "Interrupts destroy");
}

void switch2_interrupts_raise(uint32_t irq) {
    if (irq < 256) {
        irq_pending[irq] = true;
        POUND_LOG_DEBUG(&mem_logger, "IRQ %u raised", irq);
    }
}

void switch2_interrupts_poll(void) {
    for (int i=0;i<256;i++) {
        if (irq_pending[i]) {
            POUND_LOG_DEBUG(&mem_logger, "IRQ %u handled", i);
            irq_pending[i] = false;
        }
    }
}
