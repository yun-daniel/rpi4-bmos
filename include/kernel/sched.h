/*
 * sched.h
 * ---
 * Task and Scheduler Interface
 * ---
 * Daniel Yun
 */

#ifndef __KERNEL_SCHED_H__
#define __KERNEL_SCHED_H__

#include "common/types.h"
#include "mm/page_alloc.h"

#define TASK_STACK_SIZE     PAGE_SIZE


// ----------------------
// Task state enum
// ----------------------
typedef volatile long task_state_t;
#define TASK_READY      0
#define TASK_RUNNING    1
#define TASK_SLEEPING   2
#define TASK_ZOMBIE     3


// ----------------------
// CPU context (x19~x30, sp)
// ----------------------
typedef struct cpu_context {
    uint64_t x19;
    uint64_t x20;
    uint64_t x21;
    uint64_t x22;
    uint64_t x23;
    uint64_t x24;
    uint64_t x25;
    uint64_t x26;
    uint64_t x27;
    uint64_t x28;
    uint64_t fp;        // x29
    uint64_t lr;        // x30
    uint64_t sp;
} cpu_context_t;


// ----------------------
// Forward declaration
// ----------------------
struct task_struct;


// ----------------------
// RR entity
// ----------------------
typedef struct rr_entity {
    struct task_struct *task;
    struct rr_entity *next;
} rr_entity_t;


// ----------------------
// Task Structure
// ----------------------
typedef struct task_struct {
    cpu_context_t       context;
    uint64_t            pid;
    task_state_t        state;
    uint64_t            counter;        // time slice
    uint64_t            priority;
    void                *stack;

    rr_entity_t rr_node;
} task_struct;


// ----------------------
// Thread Union
// ----------------------
union thread_union {
    task_struct task;
    unsigned long stack[TASK_STACK_SIZE / sizeof(long)];
};


// ----------------------
// Runqueue Structure
// ----------------------
typedef struct {
    rr_entity_t *head;
    rr_entity_t *tail;
    task_struct *curr;
    task_struct *idle;
} runqueue;
extern runqueue rq;


// ----------------------
// Public scheduler API
// ----------------------
void sched_init(void);
void init_idle(task_struct *idle);
task_struct *task_create(void (*entry)(void));
void schedule(void);
void yield(void);


// ----------------------
// Global Task
// ----------------------
// There is no thread feature, so init_task should be used with define
extern union thread_union init_task_union;
#define init_task   (init_task_union.task)
//extern task_struct init_task;
extern task_struct *current;


// ----------------------
// idle entry
// ----------------------
void idle_entry(void);


// ----------------------
// Runqueue helpers
// ----------------------
void enqueue_task(task_struct *task);
void dequeue_task(task_struct *task);
task_struct *pick_next_task(void);


// ----------------------
// Context Stack
// ----------------------
void *init_stack(void *stack_base);


// ----------------------
// Context switch (arch/arm64/kernel/context.S)
// ----------------------
void switch_to(task_struct *prev, task_struct *next);


#endif // __KERNEL_SCHED_H__
