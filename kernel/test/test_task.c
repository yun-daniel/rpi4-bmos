// test_task.c
#include "kernel/sched.h"
#include "kernel/printk/printk.h"

extern void switch_to(task_struct *prev, task_struct *next);

void task_entry_A(void) {
    kprintf("[Task A] running\n");
    while (1) {
        kprintf("A");
        for (int i=0; i<100000; i++);
//        yield();
    }
}

void task_entry_B(void) {
    kprintf("[Task B] running\n");
    while (1) {
        kprintf("B");
        for (int i=0; i<100000; i++);
//        yield();
    }
}


void test_task_context_switch(void) {
    kprintf("[TEST] Task Context Switch\n");

    task_struct *task_a = task_create(task_entry_A);
    task_struct *task_b = task_create(task_entry_B);

    if (!task_a || !task_b) {
        kprintf("Task creation failed\n");
        return;
    }

    kprintf("Switching to Task A...\n");
    switch_to(current, task_a);
}
