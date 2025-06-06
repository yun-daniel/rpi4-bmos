/*
 * memset.c
 * ---
 * Memory Set Function
 * ---
 * Daniel Yun
 */

#include "common/string.h"

void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    while (n--)
        *p++ = c;
    return buf;
}
