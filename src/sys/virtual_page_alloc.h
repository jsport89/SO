#ifndef VIRTUAL_PAGE_ALLOC_H
#define VIRTUAL_PAGE_ALLOC_H

#include <stdint-gcc.h>

typedef struct {
   uint64_t physical_addy_offset : 12;
   uint64_t L1_offset : 9;
   uint64_t L2_offset : 9;
   uint64_t L3_offset : 9;
   uint64_t L4_offset : 9;
   uint64_t reserved : 16;
} virtual_addy;

typedef struct {
   uint64_t reserved_1 : 3;
   uint64_t pwt : 1;
   uint64_t pcd : 1;
   uint64_t reserved_2 : 7;
   uint64_t L4_base_addy_1 : 20;
   uint64_t L4_base_addy_2 : 20;
   uint64_t rerserved_3 : 12;
} CR3_register_entry;  /* Format of CR3 register */

typedef struct {
   uint64_t p : 1; /* present */
   uint64_t rw : 1;
   uint64_t us : 1;
   uint64_t pwt: 1;
   uint64_t pcd : 1;
   uint64_t a : 1;
   uint64_t ign : 1;
   uint64_t mbz: 2;
   uint64_t avl : 3;
   uint64_t L3_base_addy_1 : 20;
   uint64_t L3_base_addy_2 : 20;
   uint64_t available : 11;
   uint64_t nx : 1;
} L4_Entry;            /* Page Map Level 4 (PML4) */

typedef struct {
   uint64_t p : 1; /* present */
   uint64_t rw : 1;
   uint64_t us : 1;
   uint64_t pwt: 1;
   uint64_t pcd : 1;
   uint64_t a : 1;
   uint64_t ign : 1;
   uint64_t zero : 1;
   uint64_t mbz: 1;
   uint64_t avl : 3;
   uint64_t L2_base_addy_1 : 20;
   uint64_t L2_base_addy_2 : 20;
   uint64_t available : 11;
   uint64_t nx : 1;
} L3_Entry;            /* Page Directory Pointer Table (PDP) */

typedef struct {
   uint64_t p : 1; /* present */
   uint64_t rw : 1;
   uint64_t us : 1;
   uint64_t pwt: 1;
   uint64_t pcd : 1;
   uint64_t a : 1;
   uint64_t ign_1 : 1;
   uint64_t zero : 1;
   uint64_t ign_2: 1;
   uint64_t avl : 3;
   uint64_t L1_base_addy_1 : 20;
   uint64_t L1_base_addy_2 : 20;
   uint64_t available : 11;
   uint64_t nx : 1;
} L2_Entry;            /* Page Directory Table (PD) */

typedef struct {
   uint64_t p : 1; /* present */
   uint64_t rw : 1;
   uint64_t us : 1;
   uint64_t pwt: 1;
   uint64_t pcd : 1;
   uint64_t a : 1;
   uint64_t d : 1;
   uint64_t pat : 1;
   uint64_t g: 1;
   uint64_t avl : 3;
   uint64_t physical_base_addy_1 : 20;
   uint64_t physical_base_addy_2 : 20;
   uint64_t available : 11;
   uint64_t nx : 1;
} L1_Entry;             /* Page Table (PT) */

typedef struct {
   L4_Entry *L4_base;
} Page_Table;

/* Functions */
extern void *MMU_alloc_page();
extern void *MMU_alloc_pages(int num);
extern void MMU_free_page(void *);
extern void MMU_free_pages(void *, int num);
void init_page_tables(CR3_register_entry *page_table);
void * get_phys_addy(void * virtual_addy);
void map_page(void * physaddr, void * virtualaddr, unsigned int flags);



#endif /* virtual_page_alloc.h* */
