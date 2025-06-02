// vector.S

.section .text
.global vector_table
.balign 2048               /* Align 2KB (required from Arm64 vector table) */

.macro kernel_entry, el
    // Backup Stack Pointer (scratch)
    mov x21, sp

    // Allocate space for pt_regs: 34 x 8 = 272 bytes
    sub sp, sp, #272

    // Store general-purpose registers x0 ~ x30
    stp x0, x1,     [sp, #16 * 0]
    stp x2, x3,     [sp, #16 * 1]
    stp x4, x5,     [sp, #16 * 2]
    stp x6, x7,     [sp, #16 * 3]
    stp x8, x9,     [sp, #16 * 4]
    stp x10, x11,   [sp, #16 * 5]
    stp x12, x13,   [sp, #16 * 6]
    stp x14, x15,   [sp, #16 * 7]
    stp x16, x17,   [sp, #16 * 8]
    stp x18, x19,   [sp, #16 * 9]
    stp x20, x21,   [sp, #16 * 10]
    stp x22, x23,   [sp, #16 * 11]
    stp x24, x25,   [sp, #16 * 12]
    stp x26, x27,   [sp, #16 * 13]
    stp x28, x29,   [sp, #16 * 14]
    str x30,        [sp, #16 * 15]

    // Save SP_EL0 (SP)
    str x21, [sp, #248]

    // Save ELR_EL1 and SPSR_EL1
    mrs x22, ELR_EL1
    str x22, [sp, #256]
    mrs x23, SPSR_EL1
    str x23, [sp, #264]

.endm

.macro kernel_exit, el
    // Restore regs
    ldr x23, [sp, #264]
    msr SPSR_EL1, x23
    ldr x22, [sp, #256]
    msr ELR_EL1, x22

    ldr x30,        [sp, #16 * 15]
    ldp x28, x29,   [sp, #16 * 14]
    ldp x26, x27,   [sp, #16 * 13]
    ldp x24, x25,   [sp, #16 * 12]
    ldp x22, x23,   [sp, #16 * 11]
    ldp x20, x21,   [sp, #16 * 10]
    ldp x18, x19,   [sp, #16 * 9]
    ldp x16, x17,   [sp, #16 * 8]
    ldp x14, x15,   [sp, #16 * 7]
    ldp x12, x13,   [sp, #16 * 6]
    ldp x10, x11,   [sp, #16 * 5]
    ldp x8, x9,     [sp, #16 * 4]
    ldp x6, x7,     [sp, #16 * 3]
    ldp x4, x5,     [sp, #16 * 2]
    ldp x2, x3,     [sp, #16 * 1]
    ldp x0, x1,     [sp, #16 * 0]

    add sp, sp, #272

.endm



vector_table:
    // --- Current EL with SP_EL0 ---
    b el1_sync          // 0x000: Synchronous
    .balign 0x80
    b el1_irq           // 0x080: IRQ
    .balign 0x80
    b el1_fiq           // 0x100: FIQ (not typically used)
    .balign 0x80
    b el1_serror        // 0x180: SError
    .balign 0x80

    // --- Current EL with SP_ELx ---
    b el1_sync          // 0x200
    .balign 0x80
    b el1_irq           // 0x280
    .balign 0x80
    b el1_fiq           // 0x300
    .balign 0x80
    b el1_serror        // 0x380
    .balign 0x80

    // --- Lower EL using AArch64 ---
    b el1_sync          // 0x400
    .balign 0x80
    b el1_irq           // 0x480
    .balign 0x80
    b el1_fiq           // 0x500
    .balign 0x80
    b el1_serror        // 0x580
    .balign 0x80

    // --- Lower EL using AArch32 ---
    b el1_sync          // 0x600
    .balign 0x80
    b el1_irq           // 0x680
    .balign 0x80
    b el1_fiq           // 0x700
    .balign 0x80
    b el1_serror        // 0x780
    .balign 0x80


// Declare Handler
el1_sync:
    // Save contexts
    kernel_entry 1

    // Pass sp (== &pt_regs) to C
    mov x0, sp

    bl handle_sync_exception

    // Restore contexts
    kernel_exit 1

    eret

el1_irq:
    kernel_entry 1
    mov x0, sp
    bl handle_irq
    kernel_exit 1
    eret


el1_fiq:
    kernel_entry 1
    mov x0, sp
    bl handle_fiq
    kernel_exit 1
    eret

el1_serror:
    kernel_entry 1
    mov x0, sp
    bl handle_serror
    kernel_exit 1
    eret

