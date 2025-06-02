#ifndef __INIT_TASK_H__
#define __INIT_TASK_H__

#include "kernel/sched.h"

/*
#define INIT_THREAD_INFO(tsk) {     \
    .task       = &tsk,             \
}
*/

#define INIT_TASK(tsk) {            \
    .state      = 0,                \
    .counter    = 0,                \
    .priority   = 0,                \
    .stack      = NULL,             \
    .context    = {0},              \
    .rr_node    = { .task = NULL,   \
                    .next = NULL }  \
}


#endif // __INIT_TASK_H__
