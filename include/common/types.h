/*
 * types.h
 * ---
 * Common Type Definition
 * ---
 * Daniel Yun
 */

#ifndef __TYPES_H__
#define __TYPES_H__

typedef int bool;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;
typedef uint64_t            size_t;
typedef uint64_t            paddr_t;
typedef uint64_t            vaddr_t;


#define true        1
#define false       0
#define NULL        ((void *) 0)


#endif // __TYPES_H__
