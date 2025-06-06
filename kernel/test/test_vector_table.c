/*
 * test_vector_table.c
 * ---
 * Test Case for Exception
 * ---
 * Daniel Yun
 */

void test_vector_table(void) {
    __asm__ __volatile__("brk #0");
//    volatile int *invalid_ptr = (int *)0xDEADBEEF;
//    int value = *invalid_ptr;
//    kprintf("value : %d\n", &value);
}
