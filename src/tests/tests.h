#ifndef TESTS_H
#define TESTS_H
/*
 * TODO: include tests for
 * - so_string.c
 * - vga_console.c
 */

 /*
int i = 1;
while(i);
asm("int $0x21");
Test page fault
int *p = (int*)0xFFFFFFFFFFFFFFFF;
//int i = 1;
//while(i);
*p = 0;
printk("Multiboot_tags header address: %p.\n", multiboot_tags);
printk("Multiboot_tags tag_size: %d.\n", multiboot_tags->tag_size);
uint32_t i = 1;
printk("i address: %p.\n", &i);
printk("i address + 1: %p.\n", &i + 1);
*/

void run_so_stdio_tests(void);

#endif /* tests.h */
