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

   for(;;) {
      __asm__("hlt");
   }
}
