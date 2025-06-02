// test_page_alloc.c
#include "mm/page_alloc.h"
#include "kernel/printk/printk.h"


void test_page_alloc(void) {
    paddr_t page1 = alloc_pages(1);

    if (page1 != (paddr_t)NULL)
        kprintf("Page 1 allocated at 0x%lx\n", page1);
    else
        kprintf("Page 1 allocation failed\n");

    free_pages(page1, 1);
    kprintf("Page1 deallocated\n");

    paddr_t page2 = alloc_pages(1);
    if (page2 != (paddr_t)NULL)
        kprintf("Page 2 allocated at 0x%lx\n", page2);
    else
        kprintf("Page 2 allocation failed\n");

    if (page1 == page2)
        kprintf("Page reuse confirmed\n");
    else
        kprintf("Page reuse failed\n");

    free_pages(page2, 1);
    kprintf("Page2 deallocated\n");

    paddr_t page3 = alloc_pages(3);
    if (page3 != (paddr_t)NULL)
        kprintf("Page 3 allocated at 0x%lx\n", page3);
    else
        kprintf("Page 3 allocation failed\n");

    paddr_t page4 = alloc_pages(4);
    if (page4 != (paddr_t)NULL)
        kprintf("Page 4 allocated at 0x%lx\n", page4);
    else
        kprintf("Page 4 allocation failed\n");

    paddr_t page5 = alloc_pages(16385);
    if (page5 != (paddr_t)NULL)
        kprintf("Page 5 allocated at 0x%lx\n", page5);
    else
        kprintf("Page 5 allocation failed\n");
 }
