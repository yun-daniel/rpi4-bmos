/*
 * panic.c
 * ---
 * Panic Function
 * ---
 * Daniel Yun
 */

#include "common/panic.h"

void panic(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    kprintf("KERNEL PANIC: ");
    vprintf_internal(console_putc, fmt, args);
    kprintf("\n");

    va_end(args);

    kprintf("System halted.\n");

    while (1) {
        __asm__ __volatile__("wfe");
    }
}

    
