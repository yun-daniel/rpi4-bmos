// gic.c
#include "drivers/irq/gic.h"


static inline void mmio_write32(uint64_t addr, uint32_t val) {
    *(volatile uint32_t *)addr = val;
}

static inline uint32_t mmio_read32(uint64_t addr) {
    return *(volatile uint32_t *)addr;
}


void gic_init(void) {
    // 1. Enable CPU interface
    mmio_write32(GICC_PMR, 0xFF);       // Unmask all priorities
    mmio_write32(GICC_CTLR, 0x1);       // Enable CPU interface

    // 2. Enable Distributor
    mmio_write32(GICD_CTLR, 0x1);       // Enable forwarding to CPU interfaces

    // 3. Enable IRQ #30 (arbitrary test)
    mmio_write32(GICD_ISENABLER(0), (1 << 30));

    // 4. Target IRQ #30 to CPU0
    // ITARGETSR register is byte-accessed: 1bit per CPU, 8 bits per interrupt
    // IRQ 30 is in ITARGETSR7 (== 30 / 4)
    mmio_write32(GICD_ITARGETSR(7), 0x01010101);    // Route to CPU0 (bit 0)
}

uint32_t gic_ack_irq(void) {
    return mmio_read32(GICC_IAR);
}

void gic_send_eoi(uint32_t irq) {
    mmio_write32(GICC_EOIR, irq);
}
