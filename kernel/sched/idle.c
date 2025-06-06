/*
 * idle.c
 * ---
 * IDLE Task Entry
 * ---
 * Daniel Yun
 */

#include "kernel/sched.h"
#include "kernel/printk/printk.h"

void idle_entry(void) {
    kprintf("IDLE Task Running\n");
    while (1) {
        __asm__ __volatile__("wfi");
    }
}
