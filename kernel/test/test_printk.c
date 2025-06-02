// test_printk.c
#include "drivers/uart/uart.h"
#include "kernel/printk/printk.h"


void test_printk(void) {
    uart_putc('A');
    console_putc('B');
    kprintf("C\n");
}
