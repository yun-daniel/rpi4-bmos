// init_task.c
#include "kernel/init_task.h"

__attribute__((section(".bss.init_task"), aligned(TASK_STACK_SIZE)))
union thread_union init_task_union =
    { .task = INIT_TASK(init_task_union.task) };

//task_struct init_task = INIT_TASK(init_task);
