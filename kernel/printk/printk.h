/*
 * printk.h
 * ---
 * Interface for Kernel Print Functions
 * ---
 * Daniel Yun
 */

#ifndef __PRINTK_H__
#define __PRINTK_H__

#include "common/types.h"
#include "common/va.h"

void console_putc(char c);
void vprintf_internal(void (*putc)(char), const char *fmt, va_list args);
void kprintf(const char *fmt, ...);

#endif // __PRINTK_H__
