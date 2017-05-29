#ifndef VIRTUAL_PAGE_ALLOC_H
#define VIRTUAL_PAGE_ALLOC_H

#include <stdint-gcc.h>

#define KSTACKS_START 0x10000000000ULL
#define KHEAP_START 0xF0000000000ULL
#define USERSPACE_START 0x100000000000ULL

typedef struct {
   uint64_t physical_addy_offset : 12;
   uint64_t L1_offset : 9;
   uint64_t L2_offset : 9;
   uint64_t L3_offset : 9;
   uint64_t L4_offset : 9;
   uint64_t reserved : 16;
}__attribute__((packed)) virtual_addy;

typedef struct {
   uint64_t reserved_1 : 3;
   uint64_t pwt : 1;
   uint64_t pcd : 1;
   uint64_t reserved_2 : 7;
   uint64_t L4_base_addy : 40;
   uint64_t reserved_3 : 12;
}__attribute__((packed)) CR3_register_entry;  /* Format of CR3 register */

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
   uint64_t L3_base_addy : 40;
   uint64_t available : 11;
   uint64_t nx : 1;
}__attribute__((packed)) L4_Entry;            /* Page Map Level 4 (PML4) */

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
   uint64_t L2_base_addy : 40;
   uint64_t available : 11;
   uint64_t nx : 1;
}__attribute__((packed)) L3_Entry;            /* Page Directory Pointer Table (PDP) */

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
   uint64_t L1_base_addy : 40;
   uint64_t available : 11;
   uint64_t nx : 1;
}__attribute__((packed)) L2_Entry;            /* Page Directory Table (PD) */

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
   uint64_t physical_base_addy : 40;
   uint64_t available : 11;
   uint64_t nx : 1;
}__attribute__((packed)) L1_Entry;             /* Page Table (PT) */

typedef struct {
   L4_Entry *L4_base;
} Page_Table;

/* Functions */
//void * get_phys_addy(void * virtual_addy);
//void map_page(void * physaddr, void * virtualaddr, unsigned int flags);
void virtual_allocator_test(void);


#endif /* virtual_page_alloc.h* */
