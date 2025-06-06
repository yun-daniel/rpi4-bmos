/*
 * core.c
 * ---
 * Task and Scheduler Core
 * ---
 * Daniel Yun
 */

#include "kernel/sched.h"
#include "common/panic.h"
#include "kernel/printk/printk.h"


static uint64_t next_pid = 1;

task_struct idle_task;


void *init_stack(void *stack_base) {
    uint64_t *sp = (uint64_t *)((uint64_t)stack_base + TASK_STACK_SIZE);

    if ((uint64_t)sp % 16 != 0)
        sp--;

    return (void *)sp;
}


void init_idle(task_struct *idle) {

    void *stack_base = (void *)init_task_union.stack;
    if (!stack_base) {
        panic("init_idle: cannot allocate stack");
    }


    idle->pid       = 0;
    idle->state     = TASK_RUNNING;
    idle->counter   = 0;
    idle->priority  = 0;
    idle->stack     = stack_base;
    
    idle->context.x19   = 0;
    idle->context.x20   = 0;
    idle->context.x21   = 0;
    idle->context.x22   = 0;
    idle->context.x23   = 0;
    idle->context.x24   = 0;
    idle->context.x25   = 0;
    idle->context.x26   = 0;
    idle->context.x27   = 0;
    idle->context.x28   = 0;
    idle->context.fp    = 0;
    idle->context.lr    = (uint64_t)idle_entry;
    idle->context.sp    = (uint64_t)init_stack(stack_base);

    rq.idle = idle;
}


void sched_init(void) {
    kprintf("sched: initialize...\n");
    init_idle(current);
    kprintf("sched: initialized\n");
}


task_struct *task_create(void (*entry)(void)) {
    task_struct *task = (task_struct *)alloc_pages(1);
    if (!task) return NULL;

    void *stack_base = (void *)alloc_pages(1);
    if (!stack_base) {
        free_pages((paddr_t)task, 1);
        return NULL;
    }


    task->pid       = next_pid++;
    task->state     = TASK_READY;
    task->counter   = 1;
    task->priority  = 1;
    task->stack     = stack_base;

    task->context.x19   = 0;
    task->context.x20   = 0;
    task->context.x21   = 0;
    task->context.x22   = 0;
    task->context.x23   = 0;
    task->context.x24   = 0;
    task->context.x25   = 0;
    task->context.x26   = 0;
    task->context.x27   = 0;
    task->context.x28   = 0;
    task->context.fp    = 0;
    task->context.lr    = (uint64_t)entry;
    task->context.sp    = (uint64_t)init_stack(stack_base);

    enqueue_task(task);
 
    return task;
}

void yield(void) {
    if (rq.curr)
        rq.curr->state = TASK_READY;
    schedule();
}


void schedule(void) {
    task_struct *next = pick_next_task();

    if (next && next != rq.curr) {
        task_struct *prev = rq.curr;
        rq.curr = next;
        next->state = TASK_RUNNING;
        switch_to(prev, next);
    }
}
