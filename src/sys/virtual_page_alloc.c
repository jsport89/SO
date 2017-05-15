/*
 * Page 139 for bit info in AMD manual
 */
#include "virtual_page_alloc.h"
#include "mmu.h"
#include "../lib/types.h"
#include "../lib/so_string.h"
#include "../lib/so_stdio.h"

/* Global */
Page_Table main_page_table;


/* Functions */
extern void *MMU_alloc_page();
extern void *MMU_alloc_pages(int num);
extern void MMU_free_page(void *);
extern void MMU_free_pages(void *, int num);
void init_page_tables(CR3_register_entry *page_table);
void * get_phys_addy(void *virtual_addy);
void map_page(void *physical_addy, void  *virtual_addy, unsigned int flags);

/* Testing */
void set_identity_map(void);


void set_identity_map() {
   uint64_t lowest_address = pf_allocator_meta.lowest_possible_address;
   uint64_t highest_address = pf_allocator_meta.highest_possible_address;

   /* Init main_page_table */
   main_page_table.L4_base = (L4_Entry *)MMU_pf_alloc();
   memset((void *)main_page_table.L4_base, 0, PAGE_FRAME_SIZE);

/* TESTING */
   uint64_t test_address = 4097;
   virtual_addy v_address;
   v_address.physical_addy_offset = test_address;
   v_address.L1_offset = (test_address >> 12);
   v_address.L2_offset = (test_address >> 21);
   v_address.L3_offset = (test_address >> 30);
   v_address.L4_offset = (test_address >> 39);


   printk("\nphys_offset: %u.\n", v_address.physical_addy_offset);
   printk("L1_offset: %u.\n", v_address.L1_offset);

   printk("\nLowest Address: %lu.\n", lowest_address);
   printk("Highest Address: %lu.\n", highest_address);

   printk("\nFirst L4_Entry p: %u.\n", main_page_table.L4_base->p);
   printk("First L4_Entry rw: %u.\n", main_page_table.L4_base->rw);
   printk("First L4_Entry L3_base_1: %u.\n", main_page_table.L4_base->L3_base_addy_1);
   printk("First L4_Entry L3_base_2: %u.\n", main_page_table.L4_base->L3_base_addy_2);

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

   for (uint64_t cur_address = lowest_address; cur_address < highest_address; cur_address += PAGE_FRAME_SIZE) {
      // Put address in vadd struct
      v_address.physical_addy_offset = cur_address;
      v_address.L1_offset = (cur_address >> 12);
      v_address.L2_offset = (cur_address >> 21);
      v_address.L3_offset = (cur_address >> 30);
      v_address.L4_offset = (cur_address >> 39);

      L4_Entry *vadd_L4_entry = main_page_table.L4_base + v_address.L4_offset;
      if (!(vadd_L4_entry->p)) {
         uint64_t new_pf = (uint64_t)MM_pf_alloc();
         vadd_L4_entry->p = 1;
         vadd_L4_entry->rw = 1;
         vadd_L4_entry->L3_base_addy_1 = new_pf;
         vadd_L4_entry->L3_base_addy_2 = new_pf >> 20;
      }

      uint64_t L3_base =(vadd_L4_entry->L3_base_addy2 << 20) ) | vadd_L4_entry->L3_base_addy_1;
      L3_Entry *vadd_L3_entry = L3_base + v_address.L3_offset;
      if (!(vadd_L3_entry->p)) {
         uint64_t new_pf = (uint64_t)MM_pf_alloc();
         vadd_L3_entry->p = 1;
         vadd_L3_entry->rw = 1;
         vadd_L3_entry->L2_base_addy_1 = new_pf;
         vadd_L3_entry->L2_base_addy_2 = new_pf >> 20;
      }

      uint64_t L2_base =(vadd_L3_entry->L2_base_addy2 << 20) ) | vadd_L3_entry->L2_base_addy_1;
      L2_Entry *vadd_L2_entry = L2_base + v_address.L2_offset;
      if (!(vadd_L2_entry->p)) {
         uint64_t new_pf = (uint64_t)MM_pf_alloc();
         vadd_L2_entry->p = 1;
         vadd_L2_entry->rw = 1;
         vadd_L2_entry->L1_base_addy_1 = new_pf;
         vadd_L2_entry->L1_base_addy_2 = new_pf >> 20;
      }

      uint64_t L1_base =(vadd_L2_entry->L1_base_addy2 << 20) ) | vadd_L2_entry->L1_base_addy_1;
      L1_Entry *vadd_L1_entry = L1_base + v_address.L1_offset;
      if (!(vadd_L1_entry->p)) {
         uint64_t new_pf = (uint64_t)MM_pf_alloc();
         vadd_L1_entry->p = 1;
         vadd_L1_entry->rw = 1;
         vadd_L1_entry->L1_base_addy_1 = new_pf;
         vadd_L1_entry->L1_base_addy_2 = new_pf >> 20;
      }
   }

   /* Create L4 - L2 Tables
   main_page_table.L4_base = MMU_pf_alloc();
   main_page_table.L3_base = MMU_pf_alloc();
   main_page_table.L2_base = MMU_pf_alloc();
   */

   /* TODO: Set CR3 base address to main_page_table L4_base

   memset((void*)main_page_table.L4_base, 0, PAGE_FRAME_SIZE);
   main_page_table.L4_base->p = 1;
   main_page_table.L4_base->L3_base_addy_1 = main_page_table.L3_base;
   main_page_table.L4_base->L3_base_addy_2 = main_page_table.L3_base >> 44;

   main_page_table.L3_base->p = 1;
   main_page_table.L3_base->L2_base_addy_1 = main_page_table.L2_base;
   main_page_table.L3_base->L2_base_addy_2 = main_page_table.L2_base >> 44;

   main_page_table.L2_base->p = 1;
   */
   return;
}


/* Implementations */


void init_page_tables(CR3_register_entry *page_table) {

   /* Load page table into CR3 */
/*
   asm("mov eax, %src"
       "mov cr3, eax" :: [src] "m" (page_table));
 */

/* Might be set already...
   asm("mov eax, cr0");
   asm("or eax, 0x80000001");
   asm("mov cr0, eax");
 */
}

/*
 * + Get page map base from CR3
 * + Extract L4 offset from virtual_addy
 * + CHECK FOR PRESENT BIT
 * + Get entry L4 Entry to get to L3...
 *   - Repeat for L3 - L1
 * + Return L1 address
 */
void *get_phys_addy(void *virtual_addy) {
/*
   unsigned long pdindex = (unsigned long)virtualaddr >> 22;
      unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;

      unsigned long * pd = (unsigned long *)0xFFFFF000;
      // Here you need to check whether the PD entry is present.

      unsigned long * pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
      // Here you need to check whether the PT entry is present.

      return (void *)((pt[ptindex] & ~0xFFF) + ((unsigned long)virtualaddr & 0xFFF));



   register uint64_t L4_base asm("cr3");

   unsigned long base = L4_base;
   unsigned long offset = (unsigned long)virtual_addy >> ;
 */
 /* Check for present bit */
   return NULL;
}

void map_page(void *physical_addy, void  *virtual_addy, unsigned int flags) {
/*
   // Make sure that both addresses are page-aligned.

   unsigned long pdindex = (unsigned long)virtualaddr >> 22;
   unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;

   unsigned long * pd = (unsigned long *)0xFFFFF000;
   // Here you need to check whether the PD entry is present.
   // When it is not present, you need to create a new empty PT and
   // adjust the PDE accordingly.

   unsigned long * pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
   // Here you need to check whether the PT entry is present.
   // When it is, then there is already a mapping present. What do you do now?

   pt[ptindex] = ((unsigned long)physaddr) | (flags & 0xFFF) | 0x01; // Present

   // Now you need to flush the entry in the TLB
   // or you might not notice the change.
 */
   return;
}
