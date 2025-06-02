#include "drivers/timer/timer.h"
#include "common/types.h"
#include "kernel/printk/printk.h"


static inline uint32_t read_cntfrq(void) {
    uint32_t val;
    __asm__ __volatile__(
        "mrs %0, cntfrq_el0"
        : "=r"(val)
    );
    return val;
}

static inline void write_cntp_tval(uint32_t val) {
    __asm__ __volatile__(
        "msr cntp_tval_el0, %0"
        :
        : "r"(val)
    );
}

static inline void write_cntp_ctl(uint32_t val) {
    __asm__ __volatile__(
        "msr cntp_ctl_el0, %0"
        :
        : "r"(val)
    );
}


void timer_init(void) {
    uint32_t freq = read_cntfrq();      // ex: 6200000Hz
    write_cntp_tval(freq / 2);          // fire in 0.5 secondsa
    write_cntp_ctl(1);                  // enable = 1, imask = 0, istatus = don't care
}

void timer_reset(void) {
    uint32_t freq = read_cntfrq();
    write_cntp_tval(freq / 2);          // re-arm the timer for next 0.5s
}

void timer_handler(void) {
    timer_reset();
    kprintf("tick!\n");
}
