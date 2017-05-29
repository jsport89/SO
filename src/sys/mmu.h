/*
 * mmu.h (memory management unit) - contains all functions
 * for interfacing with the page frame and virtual page allocators.
 */
#ifndef MMU_H
#define MMU_H

#include "page_alloc.h"

#define PAGE_FRAME_SIZE 4096


/* Physical PF Functions */
extern void init_pf(Fixed_Header *from_grub);
extern void *MMU_pf_alloc(void);
extern void MMU_pf_free(void *pf);

/* Virtual PF Functions */
extern void *MMU_alloc_page();
extern void *MMU_alloc_pages(int num);
extern void MMU_free_page(void *v_add);
extern void MMU_free_pages(void *v_add, int num);
void init_page_tables(void);

/* Testing */
void *map_page_2(uint64_t v_add);
//void page_alloc_test(void);

#endif /* mmu.h */
