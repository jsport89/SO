/* kernel.c - Entry point for kernel */
/* #include "drivers/load_drivers.h" (not needed) */

#include "drivers/init_drivers.h"
#include "drivers/interrupts.h"
#include "drivers/tss.h"
#include "lib/so_stdio.h"
#include "tests/tests.h"
#include "sys/mmu.h"
#include "lib/so_stdlib.h"

// Testing
#include "sys/virtual_page_alloc.h"

int kernel_main(Fixed_Header *multiboot_tags)  {

   setup_tss();

   init_drivers();

   init_pf(multiboot_tags);

   init_page_tables();

   printk("\nSO - Somewhat Operating %s\n\n", "Operating System");

//   virtual_allocator_test();
//   kmalloc_lib_test();

   /* infinite loop */
   for(;;) {
      __asm__("hlt");
   }
}
