/* kernel.c - Entry point for kernel */
#include "drivers/load_drivers.h"
#include "drivers/init_drivers.h"
#include "lib/so_stdio.h"
#include "tests/tests.h"


int kernel_main() {

   /* Init drivers */
   init_drivers();

   printk("\nSO - Somewhat Operating %s\n\n", "Operating System");

   /* Call Test code here */

   /* run_so_stdio_tests(); */
   keyboard_poll_scancodes();

   for(;;)
      __asm__("hlt");
}
