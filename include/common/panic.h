// panic.h
#ifndef __PANIC_H__
#define __PANIC_H__

#include "kernel/printk/printk.h"
#include "va.h"


#define PANIC(fmt, ...) \
    do { \
        kprintf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        panic(fmt, ##__VA_ARGS__); \
    } while (0)

void panic(const char *fmt, ...);


#endif // __PANIC_H__
