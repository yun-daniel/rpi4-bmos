// pick.c
#include "kernel/sched.h"


task_struct *pick_next_task(void) {
    if (!rq.curr)
        return NULL;

    rr_entity_t *node = rq.head;
    while (node) {
        if (node->task->state == TASK_READY && node->task != rq.curr) {
            return node->task;
        }
        node = node->next;
    }

    return rq.idle;
}
