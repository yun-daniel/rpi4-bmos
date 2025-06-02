// console_putc.c
#include "drivers/uart/uart.h"

void console_putc(char c) {
    if (c == '\n')
        uart_putc('\r');    // CRLF
    uart_putc(c);
}
