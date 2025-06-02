// page_alloc.h
#ifndef __PAGE_ALLOC_H__
#define __PAGE_ALLOC_H__

#include "common/types.h"

#define PAGE_SIZE       4096UL
#define PAGE_SHIFT      12


void    page_alloc_init(void);
paddr_t alloc_pages(size_t num_pages);
void    free_pages(paddr_t addr, size_t num_pages);


#endif // __PAGE_ALLOC_H__
