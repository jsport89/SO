#ifndef TSS_H
#define TSS_H
#include <stdint-gcc.h>

/* Expose gdt */
extern void *gdt64;
extern void *tss_descriptor;

/* Typedefs */
typedef struct {
   uint16_t segment_limit_1;
   uint16_t base_address_1;
   uint8_t base_address_2;
   uint8_t type : 4;                      /* Interrupt or trap */
   uint8_t zero : 1;
   uint8_t dpl : 2;                       /* descriptor privilege level*/
   uint8_t present : 1;
   uint8_t segment_limit_2 : 4;
   uint8_t avl : 1;
   uint8_t empty : 2;
   uint8_t granularity : 1;
   uint8_t base_address_3;
   uint32_t base_address_4;
   uint32_t reserved;
}__attribute__((packed)) TSS_Descriptor;  /* 16 bytes */

typedef struct {
  uint16_t rpl : 2;                       /* request privilege level */
  uint16_t ti : 1;                        /* table indicator */
  uint16_t selector_index : 13;
}__attribute__((packed)) TSS_Selector;    /* 2 bytes */

typedef struct {
   uint32_t reserved_1;
   uint64_t RSP0;
   uint64_t RSP1;
   uint64_t RSP2;
   uint64_t reserved_2;
   uint64_t IST1;
   uint64_t IST2;
   uint64_t IST3;
   uint64_t IST4;
   uint64_t IST5;
   uint64_t IST6;
   uint64_t IST7;
   uint64_t reserved_3;
   uint16_t reserved_4;
   uint16_t io_map_base_address;
  /* uint32_t io_permission_bitmap; */    /* Permission bitmap? */

}__attribute__((packed)) TSS;

/* Functions */
void setup_tss(void);

#endif /* tss.h */
