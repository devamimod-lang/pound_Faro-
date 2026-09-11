#pragma once
#include <stdint.h>
#include <stdbool.h>

bool switch2_interrupts_init(void);
void switch2_interrupts_destroy(void);
void switch2_interrupts_raise(uint32_t irq);
void switch2_interrupts_poll(void);
