/*
 * mmu.h (memory management unit) - contains all functions
 * for interfacing with the page frame and virtual page allocators.
 */
#ifndef MMU_H
#define MMU_H

#include "page_alloc.h"

/* Functions */
extern void init_pf(Fixed_Header *from_grub);
extern void *MMU_pf_alloc(void);
extern void MMU_pf_free(void *pf);

void page_alloc_test();


/* Testing */
void set_identity_map(void);

#endif /* mmu.h */
