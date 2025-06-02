// runqueue.c
#include "kernel/sched.h"


runqueue rq = {
    .head = NULL,
    .tail = NULL,
    .curr = NULL,
    .idle = NULL
};

void enqueue_task(task_struct *task) {
    rr_entity_t *node = &task->rr_node;
    node->task = task;
    node->next = NULL;

    if (!rq.head) {
        rq.head = rq.tail = node;
    }
    else {
        rq.tail->next = node;
        rq.tail = node;
    }

    if (!rq.curr)
        rq.curr = task;
}

void dequeue_task(task_struct *task) {
    rr_entity_t *prev = NULL;
    rr_entity_t *curr = rq.head;

    while (curr) {
        if (curr->task == task) {
            if (prev)
                prev->next = curr->next;
            else
                rq.head = curr->next;

            if (rq.tail == curr)
                rq.tail = prev;

            if (rq.curr == task)
                rq.curr = rq.head? rq.head->task : NULL;

            break;
        }
        prev = curr;
        curr = curr->next;
    }

    task->rr_node.next = NULL;
}
