#include "init_drivers.h"
#include "interrupts.h"
#include "keyboard.h"
#include "ps2.h"
#include "serial_output.h"
#include "vga_console.h"
#include "../lib/so_stdio.h"

void init_drivers(void);

void init_drivers() {

   CLI /* Disable interrupts */

   VGA_clear();
   printk("Initializing.. ");

   ps2_init();
   init_interrupt_environment();
   keyboard_init();
   SER_init();


   STI

   printk("\n\n");
}
