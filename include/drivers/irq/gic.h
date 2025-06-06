/*
 * gic.h
 * ---
 * Interface for GIC
 * ---
 * Daniel Yun
 */

#ifndef __GIC_H__
#define __GIC_H__

#include "common/types.h"


// GIC base addresses (RPi4)
#define GICD_BASE           0xFF841000UL
#define GICC_BASE           0xFF842000UL

// GIC Distributor registers
#define GICD_CTLR           (GICD_BASE + 0x000)
#define GICD_ISENABLER(n)   (GICD_BASE + 0x100 + ((n) * 4))
#define GICD_ITARGETSR(n)   (GICD_BASE + 0x800 + ((n) * 4))

// GIC CPU interface registers
#define GICC_CTLR           (GICC_BASE + 0x000)
#define GICC_PMR            (GICC_BASE + 0x004)
#define GICC_IAR            (GICC_BASE + 0x00C)
#define GICC_EOIR           (GICC_BASE + 0x010)


// Public API
void        gic_init(void);
uint32_t    gic_ack_irq(void);
void        gic_send_eoi(uint32_t irq);


#endif // __GIC_H__
