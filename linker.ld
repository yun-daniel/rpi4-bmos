/* linker.ld */
ENTRY(_start)


SECTIONS {
    . = 0x00080000;                 /* Default loaded kernel address at RPi4 */
    __kernel_base = .;

    .text : {
        KEEP(*(.text._start))       /* Kernel initialization */
        *(.text .text*)
    } :text_seg

    .rodata : ALIGN(4) {
        *(.rodata .rodata.*)
    } :rodata_seg

    .data : ALIGN(4) {
        *(.data .data.*)
    } :data_seg

    .bss : ALIGN(4) {
        __bss = .;
        *(.bss .bss.* .sbss .sbss.*)
        . = ALIGN(0x1000);
        *(.bss.init_task)
        *(COMMON)
        __bss_end = .;
    } :data_seg

    . = ALIGN(16);                  /* According to AAPCS64, must be aligned to 16 bytes */
    __stack_bottom = .;
    . += 64 * 1024;                 /* 64KB stack */
    __stack_top = .;

    . = ALIGN(4096);
    __free_ram = .;
    . += 64 * 1024 * 1024;          /* 64MB */
    __free_ram_end = .;
}

PHDRS {
    text_seg    PT_LOAD FLAGS(5);   /* R | X */
    rodata_seg  PT_LOAD FLAGS(4);   /* R     */
    data_seg    PT_LOAD FLAGS(6);   /* R | W */
}
