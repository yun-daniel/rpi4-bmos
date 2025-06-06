/*
 * main.c
 * ---
 * Initial Kernel
 * ---
 * Daniel Yun
 */

#include "drivers/uart/uart.h"
#include "kernel/printk/printk.h"
#include "common/panic.h"
#include "drivers/irq/gic.h"
#include "drivers/timer/timer.h"
#include "kernel/sched.h"
#include "mm/page_alloc.h"
#include "kernel/test/test.h"
#include "common/string.h"


extern char __bss[], __bss_end[];

// TODO : move to architecture level
task_struct *current;


void start_kernel(void) {

    // [ Init Section ]
    // .bss
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);
    // UART
    uart_init();
    // GIC
    gic_init();
    // Timer
    timer_init();
    // PAGES
    page_alloc_init();
    // Scheduler
    current = &init_task;
    sched_init();


    // [ Run ]
    kprintf("--- [START] start_kernel ---\n");

    // --- TEST : printk.h ---
//    test_printk();
   
    // --- TEST : PANIC ---
//    PANIC("booted!");

    // --- TEST : Vector Table ---
//    test_vector_table();
   
    // --- TEST : PAGE Alloc ---
//    test_page_alloc();

    // --- TEST : idle task ---
//    switch_to(NULL, current);

    // --- TEST : Task context switching ---
    test_task_context_switch();


    kprintf("--- [FINISH] before inf loop ---\n");

    while (1) {
        __asm__ __volatile__("wfe");
    }

}
