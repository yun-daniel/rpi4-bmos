#include "kernel/printk/printk.h"


static void print_hex(unsigned int val, void (*putc)(char)) {
    const char *hex = "0123456789ABCDEF";

    for (int i=28; i>=0; i-=4)
        putc(hex[(val >> i) & 0xf]);
}

static void print_hex64(uint64_t value, void (*putc)(char)) {
    const char *hex = "0123456789ABCDEF";

    for (int i=60; i>=0; i-=4)
        putc(hex[(value >>i) & 0xf]);
}

static void print_dec(int val, void (*putc)(char)) {
    if (val < 0) {
        putc('-');
        val = -val;
    }

    char buf[10];
    int i = 0;
    do {
        buf[i++] = '0' + (val % 10);
        val /= 10;
    } while (val);

    while (i--)
        putc(buf[i]);
}

void vprintf_internal(void (*putc)(char), const char *fmt, va_list args) {

    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            putc(*fmt);
            continue;
        }
        fmt++;      // Skip '%'


        int long_modifier = 0;
        if (*fmt == 'l') {
            long_modifier = 1;
            fmt++;
        }


        switch (*fmt) {
        case 'c':
            putc((char)va_arg(args, int));
            break;
        case 's': {
            const char *s = va_arg(args, const char *);
            while (*s) putc(*s++);
            break;
        }
        case 'd':
            print_dec(va_arg(args, int), putc);
            break;
        case 'x':
            if (long_modifier)
                print_hex64(va_arg(args, uint64_t), putc);
            else
                print_hex(va_arg(args, unsigned int), putc);
            break;
        case '%':
            putc('%');
            break;
        default:
            putc('%');
            putc(*fmt);
            break;
        }
    }

}

void kprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    vprintf_internal(console_putc, fmt, args);

    va_end(args);
}
