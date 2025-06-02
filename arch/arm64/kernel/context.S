// context.S
.global switch_to


// void switch_to(task_struct *prev, task_struct *next)
switch_to:
    // x0 : prev, x1 : next
    // x19~x28 : callee-saved registers

    // Save x19~x30 in prev->context
    stp x19, x20, [x0, #16 * 0]
    stp x21, x22, [x0, #16 * 1]
    stp x23, x24, [x0, #16 * 2]
    stp x25, x26, [x0, #16 * 3]
    stp x27, x28, [x0, #16 * 4]
    stp x29, x30, [x0, #16 * 5]

    mov x9, sp
    str x9,       [x0, #16 * 6]     // Save SP

    // Restore x19~x30 from next->context
    ldp x19, x20, [x1, #16 * 0]
    ldp x21, x22, [x1, #16 * 1]
    ldp x23, x24, [x1, #16 * 2]
    ldp x25, x26, [x1, #16 * 3]
    ldp x27, x28, [x1, #16 * 4]
    ldp x29, x30, [x1, #16 * 5]

    ldr x9,       [x1, #16 * 6]
    mov sp, x9                      // Restore SP

    ret
