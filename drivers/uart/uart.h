// uart.h
#ifndef __UART_H__
#define __UART_H__


// PL011 UART register
#define UART0_BASE      0xFE201000

#define UART0_DR        (*(volatile unsigned int *)(UART0_BASE + 0x00))
#define UART0_FR        (*(volatile unsigned int *)(UART0_BASE + 0x18))
#define UART0_IBRD      (*(volatile unsigned int *)(UART0_BASE + 0x24))
#define UART0_FBRD      (*(volatile unsigned int *)(UART0_BASE + 0x28))
#define UART0_LCRH      (*(volatile unsigned int *)(UART0_BASE + 0x2C))
#define UART0_CR        (*(volatile unsigned int *)(UART0_BASE + 0x30))

#define UART0_FR_TXFF   (1 << 5)    // Transmit FIFO Full
#define UART0_FR_RXFE   (1 << 4)    // Receive FIFO Empty


void uart_init(void);
void uart_putc(char c);
char uart_getc(void);


#endif // __UART_H__
