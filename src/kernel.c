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

   printk("\nSO - Somewhat Operating %s\n\n", "Operating System");


/* Page Alloc Testing
 * alloc alloc free free alloc alloc
 * 1     2     1    2    2     1
 */
   uint64_t first_page = (uint64_t)MMU_pf_alloc();
   printk("First page address: %u.\n", first_page);


   uint64_t second_page = (uint64_t)MMU_pf_alloc();
   printk("Second page address: %u.\n", second_page);

   uint64_t third_page = (uint64_t)MMU_pf_alloc();
   printk("Third page address: %u.\n", third_page);

   MMU_pf_free((void*)first_page);
   MMU_pf_free((void*)second_page);
   MMU_pf_free((void*)third_page);

   uint64_t fourth_page = (uint64_t)MMU_pf_alloc();
   printk("Fourth page address: %u.\n", fourth_page);

   uint64_t fifth_page = (uint64_t)MMU_pf_alloc();
   printk("Fifth page address: %u.\n", fifth_page);

   uint64_t sixth_page = (uint64_t)MMU_pf_alloc();
   printk("Sixth page address: %u.\n", sixth_page);

   uint64_t sev_page = (uint64_t)MMU_pf_alloc();
   printk("Seventh page address: %u.\n", sev_page);


   /* infinite loop */
   for(;;) {
      __asm__("hlt");
   }
}
