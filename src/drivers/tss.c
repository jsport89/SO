#include "tss.h"
#include "interrupts.h"
#include "../lib/so_string.h"
#include "../lib/so_stdio.h"

#define TSS_DESCRIPTOR_SIZE 16
#define TSS_SELECTOR_SIZE 2
#define TSS_SIZE 104
#define TSS_TYPE 0x9
#define NUM_OF_IST_STACKS 7
#define IST_STACK_SIZE 4096


/* Globals */
static TSS_Descriptor SO_TSS_Descriptor;
static TSS_Selector SO_TSS_Selector;
static TSS SO_TSS;
char IST_STACKS[NUM_OF_IST_STACKS][IST_STACK_SIZE];


/* Prototypes */
static void init_tss_descriptor(void);
static void init_tss_selector(void);
static void init_tss(void);
static void configure_tss_descriptor(void);
static void configure_tss_selector(void);
static void configure_tss(void);
void setup_tss(void);


/* Functions */
static void init_tss_descriptor() {
   memset(&SO_TSS_Descriptor, 0, TSS_DESCRIPTOR_SIZE);
}

static void init_tss_selector() {
   memset(&SO_TSS_Selector, 0, TSS_SELECTOR_SIZE);
}

static void init_tss() {
   memset(&SO_TSS, 0, TSS_SIZE);
}

static void configure_tss_descriptor() {
   uint64_t tss_address = (uint64_t)&SO_TSS;

   SO_TSS_Descriptor.segment_limit_1 = TSS_SIZE;
   SO_TSS_Descriptor.base_address_1 = tss_address & 0xFFFF;
   SO_TSS_Descriptor.base_address_2 = (tss_address >> 16) & 0xFF;
   SO_TSS_Descriptor.type = TSS_TYPE;
   SO_TSS_Descriptor.present = 1;
   SO_TSS_Descriptor.base_address_3 = (tss_address >> 24) & 0xFF;
   SO_TSS_Descriptor.base_address_4 = tss_address >> 32;
}

static void configure_tss_selector() {
   SO_TSS_Selector.rpl = 0;
   SO_TSS_Selector.ti = 0;
   SO_TSS_Selector.selector_index = 2;/*0x10;*/
}

static void configure_tss() {
/*
 * Put addresses in ISTs to reserved blocks
 */
   SO_TSS.IST1 = (uint64_t)&IST_STACKS[0][IST_STACK_SIZE - 2];
   SO_TSS.IST2 = (uint64_t)&IST_STACKS[1][IST_STACK_SIZE - 2];
   SO_TSS.IST4 = (uint64_t)&IST_STACKS[2][IST_STACK_SIZE - 2];
}

/*
 * + Initialize tss selector and descriptor
 * + Configure tss selector and descriptor
 * + Copy tss_descriptor into gdt
 * + Load selector into IR
 * + Set stacks for Faults
 */
void setup_tss() {

   init_tss_selector();
   init_tss_descriptor();
   init_tss();

   configure_tss_descriptor();
   configure_tss_selector();
   configure_tss();

   memcpy(&tss_descriptor, &SO_TSS_Descriptor, TSS_DESCRIPTOR_SIZE);

/* DEBUGGIN
   int i = 1;
   while(i);
*/

   asm("ltr %0"::"m"(SO_TSS_Selector));
}


/*
1. A struct for the TSS
2. A strcut for the TSS descriptor
3. A strcut for the TSS selector
4. To make `gdt64` global in your `boot.asm`
5. To change the section that `gdt64` is in from `.rodata` to `.data`
6. Make an extern for `gdt64` e.g. `extern void *gdt64`
7. Fill out your TSS descriptor, selector (put the correct offset for the TSS descriptor in the proper bit possition), and zero out the TSS
8. `memcpy` your descriptor to the correct place in the GDT
9. Load TSS with the `ltr` instruction
 */
