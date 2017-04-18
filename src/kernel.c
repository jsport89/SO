/* kernel.c - Entry point for kernel */
#include "drivers/load_drivers.h"
#include "lib/so_stdio.h"


int kernel_main() {

/* Add init func of drivers */
   VGA_clear();

   printk("SO - Somewhat Operating %s\n", "Operating System");


   keyboard_poll_scancodes();

   /* Compartmentalize Test Code */

   for(;;)
      __asm__("hlt");
}
