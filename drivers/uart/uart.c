// uart.c
#include "uart.h"


void uart_init(void) {
    UART0_CR    = 0x00000000;   // Disable UART
    UART0_IBRD  = 1;            // Baud rate divisor (for 115200bps)
    UART0_FBRD  = 40;           // Fractional Baud rate divisor
    UART0_LCRH  = (3 << 5);     // 8-bit, no parity, 1 stop bit
    UART0_CR    = (1 << 0) | (1 << 8) | (1 << 9);   // UART enable, TX enable, RX enable
}

void uart_putc(char c) {
    // Wait until FIFO not full
    while (UART0_FR & UART0_FR_TXFF)
        ;
    UART0_DR = (unsigned int)c;
}

char uart_getc(void) {
    // Wait until FIFO not empty
    while (UART0_FR & UART0_FR_RXFE);
    return UART0_DR;
}
