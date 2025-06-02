#include "common/types.h"
#include "common/regs.h"
#include "common/panic.h"
#include "drivers/irq/gic.h"
#include "drivers/timer/timer.h"
#include "kernel/sched.h"


static inline uint64_t read_esr_el1(void) {
    uint64_t val;
    __asm__ __volatile__(
        "mrs %0, esr_el1"
        : "=r"(val)
    );
    return val;
}

static inline uint64_t read_elr_el1(void) {
    uint64_t val;
    __asm__ __volatile__(
        "mrs %0, elr_el1"
        : "=r"(val)
    );
    return val;
}

static inline uint64_t read_far_el1(void) {
    uint64_t val;
    __asm__ __volatile__(
        "mrs %0, far_el1"
        : "=r"(val)
    );
    return val;
}

static inline uint64_t read_spsr_el1(void) {
    uint64_t val;
    __asm__ __volatile__(
        "mrs %0, spsr_el1"
        : "=r"(val)
    );
    return val;
}

void handle_sync_exception(void) {
    uint64_t esr    = read_esr_el1();
    uint64_t elr    = read_elr_el1();
    uint64_t far    = read_far_el1();
    uint64_t spsr   = read_spsr_el1();

    panic("Synchronous exception occured.\n"
                "  ESR_EL1 = 0x%lx\n"
                "  ELR_EL1 = 0x%lx\n"
                "  FAR_EL1 = 0x%lx\n"
                "  SPSR_EL1 = 0x%lx",
                esr, elr, far, spsr);
}

void handle_irq(struct pt_regs *regs) {
    uint32_t irq = gic_ack_irq();

    switch(irq) {
        case 30:
            timer_handler();
            schedule();
            break;
        default:
            panic("Unknown IRQ: %d", irq);
    }

    gic_send_eoi(irq);
}

void handle_fiq(struct pt_regs *regs) {
    panic("Unhandled FIQ exception");
}

void handle_serror(struct pt_regs *regs) {
    panic("System Error (SError) occurred");
}

