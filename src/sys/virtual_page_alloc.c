/*
 * Page 139 for bit info in AMD manual
 * TODO:
 * + Insert code to handle race conditions
 * + Experiment with lowest address in set_identity_map (0 or 4096)
 */
#include "virtual_page_alloc.h"
#include "mmu.h"
#include "../lib/types.h"
#include "../lib/so_string.h"
#include "../lib/so_stdio.h"
#include "../drivers/interrupts.h"
#include "../drivers/PIC.h"
#include "../drivers/tss.h"
#include "../drivers/PIC.h"

/*
Virtual address layout
Phys       0x0
Kstacks    0x10000000000
Kheap      0xF0000000000
UserSpace  0x100000000000
*/


/* Globals */
Page_Table main_page_table;
uint64_t next_virtual_address = KHEAP_START;

/* Prototypes */
extern void *MMU_alloc_page();
extern void *MMU_alloc_pages(int num);
extern void MMU_free_page(void *v_add);
extern void MMU_free_pages(void *v_add, int num);
void init_page_tables(void);
void *get_phys_addy(void *v_add);
void *map_page(uint64_t v_add);
void pf_handler(int irq_num, int err, void *ar);
void set_identity_map(void);
void virtual_allocator_test(void);

/* Implementations */

void init_page_tables() {
   CR3_register_entry to_page_table;

   /* Init main_page_table */
   main_page_table.L4_base = (L4_Entry *)MMU_pf_alloc();
   memset((void *)main_page_table.L4_base, 0, PAGE_FRAME_SIZE);

   /* Init cr3 struct */
   to_page_table.reserved_1 = 0;
   to_page_table.pwt = 0;
   to_page_table.pcd = 0;
   to_page_table.reserved_2 = 0;
   to_page_table.L4_base_addy = (uint64_t)main_page_table.L4_base >> 12;
   to_page_table.reserved_3 = 0;

   set_identity_map();

   /* Set pf handler */
   IRQ_set_handler(PF_GLOBAL_IDT_INDEX, pf_handler, NULL);

   /* Load page table into CR3 */
   asm("mov %0, %%cr3"::"r" (to_page_table));
}

/*
* + Loop through addresses 4096 to highest_possible_address
*   - Put address in v_add struct
*   - Start with main page table
*   - Check if L4 entry is present and rw
*   - IF no L4 entry
*     + Create it and init
*   - Get L3 base
*   - IF no L3 entry
*     + Create it and init
*   - Get L2 base
*   ...
*/
void set_identity_map() {

 //  uint64_t lowest_address = pf_allocator_meta.lowest_possible_address;
   uint64_t highest_address = pf_allocator_meta.highest_possible_address;

   virtual_addy v_address;

   for (uint64_t cur_address = 0 /*lowest_address*/; cur_address < highest_address; cur_address += PAGE_FRAME_SIZE) {

/*  TODO: Create masks */

      // Put address in vadd struct
      v_address.physical_addy_offset = cur_address;
      v_address.L1_offset = (cur_address >> 12);
      v_address.L2_offset = (cur_address >> 21);
      v_address.L3_offset = (cur_address >> 30);
      v_address.L4_offset = (cur_address >> 39);
      v_address.reserved = 0;

   // TESTING
   //   int i = 1;
   //   while(i);

      L4_Entry *vadd_L4_entry = (L4_Entry *)(main_page_table.L4_base + v_address.L4_offset);
      if (!(vadd_L4_entry->p)) {
         uint64_t new_pf = (uint64_t)MMU_pf_alloc();
         memset((void *)new_pf, 0, PAGE_FRAME_SIZE);
         vadd_L4_entry->rw = 1;
         vadd_L4_entry->L3_base_addy = new_pf >> 12;
         vadd_L4_entry->p = 1;
      }

      L3_Entry *L3_base = (L3_Entry *)((uint64_t)vadd_L4_entry->L3_base_addy << 12);
      L3_Entry *vadd_L3_entry = (L3_Entry *)(L3_base + v_address.L3_offset);
      if (!(vadd_L3_entry->p)) {
         uint64_t new_pf = (uint64_t)MMU_pf_alloc();
         memset((void *)new_pf, 0, PAGE_FRAME_SIZE);
         vadd_L3_entry->rw = 1;
         vadd_L3_entry->L2_base_addy = new_pf >> 12;
         vadd_L3_entry->p = 1;
      }

      L2_Entry *L2_base = (L2_Entry *)((uint64_t)vadd_L3_entry->L2_base_addy << 12);
      L2_Entry *vadd_L2_entry = (L2_Entry *)(L2_base + v_address.L2_offset);
      if (!(vadd_L2_entry->p)) {
         uint64_t new_pf = (uint64_t)MMU_pf_alloc();
         memset((void *)new_pf, 0, PAGE_FRAME_SIZE);
         vadd_L2_entry->rw = 1;
         vadd_L2_entry->L1_base_addy = new_pf >> 12;
         vadd_L2_entry->p = 1;
      }

      L1_Entry *L1_base = (L1_Entry *)((uint64_t)vadd_L2_entry->L1_base_addy << 12);
      L1_Entry *vadd_L1_entry = (L1_Entry *)(L1_base + v_address.L1_offset);
      if (!(vadd_L1_entry->p)) {
         vadd_L1_entry->rw = 1;
         if (0 == cur_address) {
            vadd_L1_entry->physical_base_addy = (uint64_t)MMU_pf_alloc >> 12;
         }
         else {
            vadd_L1_entry->physical_base_addy = cur_address >> 12;
         }
         vadd_L1_entry->p = 1;
      }
   }
}

/*
 * + Get page map base from CR3
 * + Extract L4 offset from virtual_addy
 * + CHECK FOR PRESENT BIT
 * + Get entry L4 Entry to get to L3...
 *   - Repeat for L3 - L1
 * + Return L1 address
 */
/* Return address to L1 entry */
void *map_page(uint64_t v_add) {
   virtual_addy v_address;

   v_address.physical_addy_offset = v_add;
   v_address.L1_offset = (v_add >> 12);
   v_address.L2_offset = (v_add >> 21);
   v_address.L3_offset = (v_add >> 30);
   v_address.L4_offset = (v_add >> 39);
   v_address.reserved = 0;

   L4_Entry *vadd_L4_entry = (L4_Entry *)(main_page_table.L4_base + v_address.L4_offset);
   if (!(vadd_L4_entry->p)) {
     uint64_t new_pf = (uint64_t)MMU_pf_alloc();
     memset((void *)new_pf, 0, PAGE_FRAME_SIZE);
     vadd_L4_entry->rw = 1;
     vadd_L4_entry->L3_base_addy = new_pf >> 12;
     vadd_L4_entry->p = 1;
   }

   L3_Entry *L3_base = (L3_Entry *)((uint64_t)vadd_L4_entry->L3_base_addy << 12);
   L3_Entry *vadd_L3_entry = (L3_Entry *)(L3_base + v_address.L3_offset);
   if (!(vadd_L3_entry->p)) {
     uint64_t new_pf = (uint64_t)MMU_pf_alloc();
     memset((void *)new_pf, 0, PAGE_FRAME_SIZE);
     vadd_L3_entry->rw = 1;
     vadd_L3_entry->L2_base_addy = new_pf >> 12;
     vadd_L3_entry->p = 1;
   }

   L2_Entry *L2_base = (L2_Entry *)((uint64_t)vadd_L3_entry->L2_base_addy << 12);
   L2_Entry *vadd_L2_entry = (L2_Entry *)(L2_base + v_address.L2_offset);
   if (!(vadd_L2_entry->p)) {
     uint64_t new_pf = (uint64_t)MMU_pf_alloc();
     memset((void *)new_pf, 0, PAGE_FRAME_SIZE);
     vadd_L2_entry->rw = 1;
     vadd_L2_entry->L1_base_addy = new_pf >> 12;
     vadd_L2_entry->p = 1;
   }

   L1_Entry *L1_base = (L1_Entry *)((uint64_t)vadd_L2_entry->L1_base_addy << 12);
   L1_Entry *vadd_L1_entry = (L1_Entry *)(L1_base + v_address.L1_offset);
   if (!(vadd_L1_entry->p)) {
     vadd_L1_entry->rw = 1;
     vadd_L1_entry->available = 1; // For on-demand paging
   }

   return (void *)vadd_L1_entry;
}

/* FOR TESTING */
void *map_page_2(uint64_t v_add) {
   virtual_addy v_address;

   v_address.physical_addy_offset = v_add;
   v_address.L1_offset = (v_add >> 12);
   v_address.L2_offset = (v_add >> 21);
   v_address.L3_offset = (v_add >> 30);
   v_address.L4_offset = (v_add >> 39);
   v_address.reserved = 0;

   L4_Entry *vadd_L4_entry = (L4_Entry *)(main_page_table.L4_base + v_address.L4_offset);

   L3_Entry *L3_base = (L3_Entry *)((uint64_t)vadd_L4_entry->L3_base_addy << 12);
   L3_Entry *vadd_L3_entry = (L3_Entry *)(L3_base + v_address.L3_offset);

   L2_Entry *L2_base = (L2_Entry *)((uint64_t)vadd_L3_entry->L2_base_addy << 12);
   L2_Entry *vadd_L2_entry = (L2_Entry *)(L2_base + v_address.L2_offset);

   L1_Entry *L1_base = (L1_Entry *)((uint64_t)vadd_L2_entry->L1_base_addy << 12);
   L1_Entry *vadd_L1_entry = (L1_Entry *)(L1_base + v_address.L1_offset);

   return (void *)vadd_L1_entry;
}

/*
 * + Start from next available virtual addy
 * + MAP virtual addy in page table DONT alloc pf yet
 * + at L1 entry, p = 0, available = 1 (on demand)
 * + increment next virtual_address
 */
void *MMU_alloc_page() {
   int enable_ints = INTS_OFF;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   uint64_t to_return = next_virtual_address;

   // Check that next v_add is less than USERSPACE_START
   if (next_virtual_address > USERSPACE_START) {
      printk("\n\n**MMU: Can't alloc anymore page frames in v allocator.**\n\n");
      for(;;) {
        __asm__("hlt");
      }
   }

   //map_page(to_return);
   next_virtual_address += PAGE_FRAME_SIZE;

   if (enable_ints) {
      STI
   }

   return (void *)to_return;
}

/* TODO: Disable interrupts */
void *MMU_alloc_pages(int num) {
   void *first_page = MMU_alloc_page();

   for (int i = 0; i < num - 1; i++) {
      MMU_alloc_page();
   }

   return first_page;
}

/*
 * Reset v_add's L1_Entry
 * and free physical pf
 */
void MMU_free_page(void *v_add) {
   int enable_ints = INTS_OFF;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   L1_Entry *L1_Entry_to_clear = (L1_Entry *)map_page((uint64_t)v_add);
   uint64_t pf_to_free;

   if (L1_Entry_to_clear->p) {
      pf_to_free = ((uint64_t)L1_Entry_to_clear->physical_base_addy) << 12;
      MMU_pf_free((void *)pf_to_free);
   }

   if (enable_ints) {
      STI
   }
}

void MMU_free_pages(void *v_add, int num) {
   for (int i = 0; i < num; i += PAGE_FRAME_SIZE) {
      MMU_free_page((void *)((uint64_t)v_add + i));
   }
}

/*
 * In pf handler, get virtual addy from cr2, walk page table. pf_alloc page.
 * turn availble = 0, p = 1.
 */
 void pf_handler(int irq_num, int err, void *ar) {
    //register intptr_t stack_pointer asm("rsp");
    //printk("\n\nPF stack address: %x.\n", (unsigned int)stack_pointer);

/* rip(instruction pointer) that's the line that caused the interrupt */

   L1_Entry *to_set = NULL;
   uint64_t v_add_causing_pf;
   uint64_t cr3_contents;
   __asm__("movq %%cr2, %0" : "=r"(v_add_causing_pf));
   __asm__("movq %%cr3, %0" : "=r"(cr3_contents));
   to_set = (L1_Entry *)map_page(v_add_causing_pf);

/* DEBUGGING */
//   printk("Page Fault Occurred...\n");

   if (1 == to_set->available) {
      uint64_t new_pf = (uint64_t)MMU_pf_alloc();
      to_set->physical_base_addy = new_pf >> 12;
      to_set->available = 0;
      to_set->p = 1;
   }
   else {
      printk("KERN_INFO_PF: cr2 - %lu.\n", v_add_causing_pf);
      printk("KERN_INFO_PF: cr3 - %lu.\n", cr3_contents);
      printk("KERN_INFO_PF: error - %d.\n", err);
   }
/* DEBUGGING
   printk("KERN_INFO_PF: cr2 - %lu.\n", v_add_causing_pf);
   printk("KERN_INFO_PF: cr3 - %lu.\n", cr3_contents);
   printk("KERN_INFO_PF: error - %d.\n", err);
*/

 /* Debugging To Cause DF
    int *something = (int*)0xFFFFFFFFFFFFFFFF;
    *something = 0;
    divide by zero
    */
 }

void virtual_allocator_test() {
   void *test = MMU_alloc_page();
// DELETE Check that present bit is set with address...
//   L1_Entry *to_check = (L1_Entry *)map_page_2((uint64_t)test);
/*
   printk("available: %lu.\n", (uint64_t)to_check->available);
   printk("p: %lu.\n", (uint64_t)to_check->p);
   printk("rw: %lu.\n", (uint64_t)to_check->rw);
   printk("phys_base_add: %lu.\n\n", ((uint64_t)to_check->physical_base_addy) << 12);
*/
   char *char_test = (char *)test;

//0x10a155
//  int i = 1;
//  while(i);


   char_test[0] = 'a';
   char_test[1] = 'b';
   char_test[2] = '\0';

   printk("\n1st char_test address: %p. Contents: %s.\n", char_test, char_test);

/*
   printk("AFTER available: %lu.\n", (uint64_t)to_check->available);
   printk("AFTER p: %lu.\n", (uint64_t)to_check->p);
   printk("AFTER rw: %lu.\n", (uint64_t)to_check->rw);
   printk("AFTER phys_base_add: %lu.\n\n", ((uint64_t)to_check->physical_base_addy) << 12);
*/

   MMU_free_page(test);
   test = MMU_alloc_page();

   char_test = (char *)test;
   char_test[0] = 'c';
   char_test[1] = 'd';
   char_test[2] = '\0';

   printk("\n2nd char_test address: %p. Contents: %s.\n", char_test, char_test);
   MMU_free_page(test);

   while(1) {
      MMU_alloc_page();
   }

}
