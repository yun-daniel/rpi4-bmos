/*
 * start.S
 * ---
 * Kernel Entry Point
 * ---
 * Daniel Yun
 */

.section .text._start
.global _start

_start:
    // Disable Interrupt (DAIF bitset: Debug, SError, IRQ, FIQ)
    msr DAIFSet, #0xf

    // Check the current Exception Level (EL2 -> EL1)
    mrs x0, CurrentEL
    lsr x0, x0, #2  // 2-bit shift CurrentEL
    cmp x0, #2      // Check EL2 or not
    b.ne el1_ready  // Skip to el1_ready if not EL2


    // HCR_EL2 setting : setup to execute EL1 as Non-secure
    // If in EL2, move to EL1
    mov x0, #(1 << 31)  // RW=1, AArch64 mode (if not, default is AArch32)
    msr HCR_EL2, x0

    // Disable FP traps from EL2
    mrs x0, CPTR_EL2
    bic x0, x0, #(3 << 10)      // Clear TFP
    msr CPTR_EL2, x0

    // Enable FP/SIMD at EL1
    mrs x0, CPACR_EL1
    orr x0, x0, #(3 << 20)      // Set FPEN[21:20] = 0b11
    msr CPACR_EL1, x0
    isb

    // Skip for High-level setting like SCR_EL3 (RPi4 starts on EL2 usually)


    // SPSR_EL2 setting : saves status to Exception Return
    mov x0, #(0b0101)       // EL1h (Exception Level 1, Handler mode)
    mov x1, #(0b1111 << 6)  // DAIF = mask all interrupts
    orr x0, x0, x1          // x0 = 0x505
    msr SPSR_EL2, x0

    // ELR_EL2 setting : Exception Return address = el1_ready label
    adr x0, el1_ready
    msr ELR_EL2, x0

    // ERET : jump to el1_ready as Exception Return (Start from EL1 mode)
    eret


el1_ready:
    // Now running at EL1

    // Stack Pointer
    ldr x0, =__stack_top
    mov sp, x0


    // Disable MMU and caches (safe setup)
//    mrs x0, SCTLR_EL1
//    bic x0, x0, #(1 << 0)
//    bic x0, x0, #(1 << 2)
//    bic x0, x0, #(1 << 12)
//    msr SCTLR_EL1, x0
//    isb 


    // VBAR_EL1
    ldr x0, =vector_table
    msr VBAR_EL1, x0
    isb

    // Enable Interrupt
    msr DAIFClr, #2     // IRQ bit clear


    // Into C codes
    bl start_kernel


hang:
    wfe
    b hang
