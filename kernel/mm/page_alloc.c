/*
 * page_alloc.c
 * ---
 * Page Allocator
 * ---
 * Daniel Yun
 */

#include "mm/page_alloc.h"

extern char __free_ram[], __free_ram_end[];

#define MAX_PAGES   (64 * 1024 * 1024 / PAGE_SIZE)
static uint8_t  page_bitmap[MAX_PAGES];

static paddr_t  base_addr;
static size_t   total_pages;


void page_alloc_init(void) {
    paddr_t start  = (paddr_t)__free_ram;
    paddr_t end    = (paddr_t)__free_ram_end;

    // 4KB Align
    // already free_ram is aligend to 4KB in linker.ld
    // but, align it to stable
    start   = (start + PAGE_SIZE - 1 ) & ~(PAGE_SIZE - 1);
    end     = end & ~(PAGE_SIZE - 1);

    base_addr   = start;
    total_pages = (end - start) / PAGE_SIZE;

    for (size_t i=0; i<total_pages; ++i)
        page_bitmap[i] = 0;
}

paddr_t alloc_pages(size_t num_pages) {
    if (num_pages == 0 || num_pages > total_pages)
        return (paddr_t)NULL;

    for (size_t i=0; i<=(total_pages-num_pages); ++i) {
        // Check continous pages with num
        size_t j;
        for (j=0; j<num_pages; ++j) {
            if (page_bitmap[i+j]) break;
        }

        // Allocate
        if (j == num_pages) {
            for (j=0; j<num_pages; ++j)
                page_bitmap[i+j] = 1;

            return (base_addr + i * PAGE_SIZE);
        }
    }

    return (paddr_t)NULL;
}

void free_pages(paddr_t addr, size_t num_pages) {
    if (addr==(paddr_t)NULL || num_pages==0)
        return;

    if (addr<base_addr || ((addr-base_addr) % PAGE_SIZE) != 0)
        return;

    size_t index = (addr - base_addr) / PAGE_SIZE;
    if (index + num_pages > total_pages)
        return;

    for (size_t i=0; i<num_pages; ++i)
        page_bitmap[index+i] = 0;
}
