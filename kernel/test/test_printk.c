/*
 * test_printk.c
 * ---
 * Test Case for Kernel Print Functions
 * ---
 * Daniel Yun
 */

#include "drivers/uart/uart.h"
#include "kernel/printk/printk.h"


void test_printk(void) {
    uart_putc('A');
    console_putc('B');
    kprintf("C\n");
}
