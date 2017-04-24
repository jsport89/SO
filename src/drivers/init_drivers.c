#include "init_drivers.h"
#include "keyboard.h"
#include "ps2.h"
#include "vga_console.h"
#include "../lib/so_stdio.h"

void init_drivers(void);

void init_drivers() {

   VGA_clear();
   printk("Initializing.. ");

/*
   init IDT
   init PIC
 */

   ps2_init();
   keyboard_init();
   printk("\n\n");
}
