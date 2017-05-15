/* kernel.c - Entry point for kernel */
/* #include "drivers/load_drivers.h" (not needed) */

#include "drivers/init_drivers.h"
#include "drivers/interrupts.h"
#include "drivers/tss.h"
#include "lib/so_stdio.h"
#include "tests/tests.h"
#include "sys/mmu.h"

int kernel_main(Fixed_Header *multiboot_tags)  {

   setup_tss();

   init_drivers();

   init_pf(multiboot_tags);

/* Testing */
   set_identity_map();

   printk("\nSO - Somewhat Operating %s\n\n", "Operating System");


/* Page Alloc Testing
 * alloc alloc free free alloc alloc
 * 1     2     1    2    2     1
 */

   /* infinite loop */
   for(;;) {
      __asm__("hlt");
   }
}
