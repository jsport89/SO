/*
 * page_alloc.c - contains functions relevant to the page frame allocator.
 * TODO:
 * + Clean up map_available_memory_addresses
 * + Check for valid alloc'd address in free
 */
#include "page_alloc.h"
#include "mmu.h"
#include "../drivers/interrupts.h"
#include "../lib/so_stdio.h"
#include "../lib/so_string.h"
#include "../lib/types.h"
#include <stdint-gcc.h>

#define MMP_TYPE 6
#define ELF_HEADER_TYPE 9
#define USABLE 1

static int FOUND_FIRST_MMP_ENTRY = FALSE;

/* Globals */
Free_Pool pf_free_pool;

/* Prototypes */
void init_pf(Fixed_Header *from_grub);
static void init_pf_allocator(void);
static void init_free_pool(void);
static int is_free_pool_empty(void);
static void *get_pf_from_free_pool(void);
static void add_to_pf_free_pool(void *pf);
static void map_available_memory_addresses(Fixed_Header *from_grub);
extern void *MMU_pf_alloc(void);
extern void MMU_pf_free(void *pf);

/* Functions */

void init_pf(Fixed_Header *from_grub) {
   init_pf_allocator();
   init_free_pool();
   map_available_memory_addresses(from_grub);

// DELETE
/*
   printk("First address: %lu.\n", pf_allocator_meta.lowest_possible_address);
   printk("Last address: %lu.\n", pf_allocator_meta.highest_possible_address);
 */
}

static void map_available_memory_addresses(Fixed_Header *from_grub) {
   char *cur_tag = (char*)from_grub;
   int padding = 0;
   Memory_Map_Tag *mmp = NULL;
   ELF_Section_Header *esh = NULL;
   uint64_t tag_last_address = 0;
   uint32_t tag_type = 1;
   uint32_t tag_size = 0;
   uint32_t total_tags_size = ((Fixed_Header*)cur_tag)->tag_size;

// DELETE
//   printk("Initial tags total size: %d.\n", ((Fixed_Header*)cur_tag)->tag_size);


   cur_tag += 8; /* Get tag after fixed header */
   total_tags_size -= 8;

   tag_type = ((Generic_Tag *)cur_tag)->tag_type;
   tag_size = ((Generic_Tag *)cur_tag)->tag_size;

  /* Find memory map and elf section header*/
   while (cur_tag < (((char*)from_grub) + total_tags_size)) {
      tag_type = ((Generic_Tag *)cur_tag)->tag_type;
      tag_size = ((Generic_Tag *)cur_tag)->tag_size;

/* DELETE
      printk("\nFoundtag:\n");
      printk("tag_type: %d.\n", tag_type);
      printk("tag_size: %d.\n", tag_size);
 */

      if (tag_type == MMP_TYPE) {
         printk("Found memory map...\n");
         mmp = (Memory_Map_Tag *)cur_tag;
      }
      else if (tag_type == ELF_HEADER_TYPE) {
         printk("Found elf header...\n");
         esh = (ELF_Section_Header *)cur_tag;
      }
      padding = tag_size % 8 ? (8 - (tag_size % 8)) : 0;
      cur_tag += tag_size + padding ;
   }

/* Get address spaces
   printk("\n\nmmp:\ntype: %u.\nsize: %u.\nentrySize: %u.\n", mmp->tag_type, mmp->tag_size, mmp->memory_info_entry_size);
   printk("version: %u.\n\n", mmp->memory_info_entry_version);
 */
   int num_of_mem_entries = (mmp->tag_size - 16) / mmp->memory_info_entry_size;

   /* Beginning of array of memory entries */
   cur_tag = (char*)mmp;
   cur_tag += 16;

   /* loop through memory entries */
   for (int i = 0; i < num_of_mem_entries; i++) {

/* DEBUGGIN
      printk("\nMemoryEntry:\n");
      printk("StartAddress: %u.\n",((Memory_Info_Entry *)cur_tag)->starting_address);
      printk("Length: %u.\n", ((Memory_Info_Entry *)cur_tag)->length);
      printk("Type: %u.\n", ((Memory_Info_Entry *)cur_tag)->type);
 */

      uint32_t entry_type = ((Memory_Info_Entry *)cur_tag)->type;

      if ((USABLE == entry_type) && !FOUND_FIRST_MMP_ENTRY) {
         pf_allocator_meta.first_mmp_high_limit = (uint64_t)((char*)((Memory_Info_Entry *)cur_tag)->starting_address + ((Memory_Info_Entry *)cur_tag)->length);
         FOUND_FIRST_MMP_ENTRY = TRUE;
      }
      else if ((USABLE == entry_type) && FOUND_FIRST_MMP_ENTRY) {
         pf_allocator_meta.second_mmp_low_limit = (uint64_t)(((Memory_Info_Entry *)cur_tag)->starting_address);
         pf_allocator_meta.second_mmp_high_limit = pf_allocator_meta.second_mmp_low_limit + ((Memory_Info_Entry *)cur_tag)->length;
      }

      tag_last_address = ((Memory_Info_Entry *)cur_tag)->starting_address + ((Memory_Info_Entry *)cur_tag)->length;

// DELETE
//      printk("Tag Last address: %lu.\n", tag_last_address);

      if (tag_last_address > pf_allocator_meta.highest_possible_address) {
          pf_allocator_meta.highest_possible_address = tag_last_address;
      }

      cur_tag += MMP_ENTRY_SIZE;
   }

// DELETE
//   printk("PFALLOC Last address: %lu.\n", pf_allocator_meta.highest_possible_address);

 /* ELF section header
   printk("\nELF Section Header:\n");
   printk("Type: %u.\n", esh->tag_type);
   printk("Size: %u.\n", esh->tag_size);
   printk("#ofSectHeaders: %u.\n", esh->number_of_section_header_entries);
   printk("SH_entry_size: %u.\n", esh->section_header_entry_size);
   printk("index_of_section_with_string_table: %u.\n", esh->index_of_section_with_string_table);
  */

   /* Loop through elf headers */
   cur_tag = (char*)esh;
   cur_tag += 20;
   uint64_t end_of_kernel = 0;

   for (int i = 0; i < esh->number_of_section_header_entries; i++) {

/* DEBUGGIN
      printk("\nelf tag:\n");
      printk("start address: %u.\n", ((Section_Header_Entry *)cur_tag)->segment_address);
      printk("end address: %u.\n", ((Section_Header_Entry *)cur_tag)->segment_address + ((Section_Header_Entry *)cur_tag)->segment_size);
      printk("size: %u.\n", ((Section_Header_Entry *)cur_tag)->segment_size);
      printk("type: %u.\n", ((Section_Header_Entry *)cur_tag)->section_type);
      printk("flags: %u.\n", ((Section_Header_Entry *)cur_tag)->flags);
  */
      end_of_kernel = ((Section_Header_Entry *)cur_tag)->segment_address + ((Section_Header_Entry *)cur_tag)->segment_size;

      if (pf_allocator_meta.second_mmp_low_limit < end_of_kernel) {
         end_of_kernel = end_of_kernel % PAGE_FRAME_SIZE ? end_of_kernel + PAGE_FRAME_SIZE - (end_of_kernel % PAGE_FRAME_SIZE) : end_of_kernel;
         pf_allocator_meta.second_mmp_low_limit = end_of_kernel;
      }


      cur_tag += SH_ENTRY_SIZE;
   }

/* DEBUGGIN
   printk("\nPF_ALLOC_META:\n");
   printk("first_low = %u.\n", pf_allocator_meta.first_mmp_low_limit);
   printk("first_high = %u.\n", pf_allocator_meta.first_mmp_high_limit);
   printk("second_low = %u.\n", pf_allocator_meta.second_mmp_low_limit);
   printk("second_high = %u.\n", pf_allocator_meta.second_mmp_high_limit);
 */
}

/*
  + Check for available pages in free pool
  + Start Allocating from address 4000+
  + If allocations exceed 654336 from 1st mmp entry
    - Start allocating from second entry MINUS kernel's area
  + If we exceed max address from 2nd mmp entry, throw error
*/
void *MMU_pf_alloc(void) {

   int enable_ints = INTS_OFF;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   uint64_t next_address = pf_allocator_meta.next_available_address;
   void *free_page = NULL;

   /* Init next_address */
   memset((void*)next_address, 0, PAGE_FRAME_SIZE);

   if (!is_free_pool_empty()) {
      free_page = get_pf_from_free_pool();

      if (enable_ints) {
         STI
      }

      return free_page;
   }

   if (next_address > pf_allocator_meta.second_mmp_high_limit) {
      printk("\n\n**MMU: Can't alloc anymore page frames in pf allocator.**\n\n");
      for(;;) {
        __asm__("hlt");
      }
   }
   else if ((next_address >= pf_allocator_meta.first_mmp_high_limit) &&
       (next_address < pf_allocator_meta.second_mmp_low_limit)) {
      pf_allocator_meta.next_available_address = pf_allocator_meta.second_mmp_low_limit;
      next_address = pf_allocator_meta.next_available_address;
      free_page = (void*)next_address;
   }
   else {
      free_page = (void*)next_address;
   }

   pf_allocator_meta.next_available_address += PAGE_FRAME_SIZE;

   if (enable_ints) {
      STI
   }

   return free_page;
}

/* TODO: Check for valid address that's been alloc'd */
void MMU_pf_free(void *pf) {
   int enable_ints = INTS_OFF;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   add_to_pf_free_pool(pf);

   if (enable_ints) {
      STI
   }

}

static void init_pf_allocator() {
   pf_allocator_meta.first_mmp_low_limit = FIRST_AVAILABLE_ADDRESS;
   pf_allocator_meta.first_mmp_high_limit = 0;
   pf_allocator_meta.second_mmp_low_limit = 0;
   pf_allocator_meta.second_mmp_high_limit = 0;
   pf_allocator_meta.next_available_address  = FIRST_AVAILABLE_ADDRESS;
   pf_allocator_meta.lowest_possible_address = FIRST_AVAILABLE_ADDRESS;
   pf_allocator_meta.highest_possible_address = 0;
}

/* HELPERS */

static void init_free_pool() {
   pf_free_pool.size = 0;
   pf_free_pool.last_free_page = 0;
}

static int is_free_pool_empty() {
   return pf_free_pool.size == EMPTY;
}

/*
 * + Store last_free_page
 * + Update last_free_page
 *   - IF size > 1, to previous free page in list
 *   - ELSE last_free_page = 0
 * + Decrement free pool size
 */
static void *get_pf_from_free_pool() {
   uint64_t free_page = pf_free_pool.last_free_page;
   uint64_t size = pf_free_pool.size;

   if (size > 1) {
      pf_free_pool.last_free_page = *((uint64_t *)free_page);
   }
   else {
      pf_free_pool.last_free_page = 0;
   }

   pf_free_pool.size--;

   return  (void*)free_page;
}

/*
 * Clear pf
 * IF size == 0, last_free_page = pf
 * ELSE, connect pf to last_free_page , update last_free_page to pf
 * Increment free pool size
 */
static void add_to_pf_free_pool(void *pf) {
   memset(pf, 0, PAGE_FRAME_SIZE);

   if (is_free_pool_empty()) {
      pf_free_pool.last_free_page = (uint64_t)pf;
   }
   else {
      *((uint64_t *)pf) = pf_free_pool.last_free_page;
      pf_free_pool.last_free_page = (uint64_t)pf;
   }

   pf_free_pool.size++;
}

/*
void page_alloc_test() {
   uint64_t *page;
   int i;
   while (1) {
      for (i = 1; page = (uint64_t *)MMU_pf_alloc(); i++) {
         *page = i;
         printk("Page value: %u.\n", *page);
      }
   }

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
}
 */
