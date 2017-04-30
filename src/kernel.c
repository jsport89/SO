/* kernel.c - Entry point for kernel */
#include "drivers/load_drivers.h"
#include "drivers/init_drivers.h"
#include "drivers/interrupts.h"
#include "lib/so_stdio.h"
#include "tests/tests.h"

int kernel_main() {

   init_drivers();

   printk("\nSO - Somewhat Operating %s\n\n", "Operating System");

   //asm("int $0x21");

/* Test page fault
int *p = (int*)0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF;
int i = 1;
while(i);
*p = 0;
*/

/* To load TSS
uint16_t selector = 0x40;
asm("ltr %0"::"m"(selector));
*/

   int i = 1;
   while(i);
   printk("test\n");
   for(;;) {
      __asm__("hlt");
   }
}
