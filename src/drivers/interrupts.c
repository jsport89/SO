/*
 * interrupts.c - Contains implementations of
 * interrupt functions.
 * TODO:
 * - implement setting addresses in target offsets
 *   for each IDT entry
 */
#include "interrupts.h"
#include "PIC.h"
#include "../lib/so_string.h"
#include "../helpers/ioaccess.h"

#define MASTER_PIC_NEW_OFFSET 0x20
#define SLAVE_PIC_NEW_OFFSET 0x70

Interrupt_Descriptor Global_IDT[IDT_SIZE];

/* Prototypes */
void init_interrupt_environment(void);
void IRQ_handler(void);

/* Sets up IDT and tells CPU where it's at */
void init_interrupt_environment() {
   size_t Global_IDT_size;

   Global_IDT_size = sizeof(Interrupt_Descriptor) * IDT_SIZE;

   /* Init IDT */
   memset((void*)Global_IDT, 0, Global_IDT_size);

   /* set addresses of irq_wrapper_X to each entry in Global IDT */

   /* Calid lidt to tell CPU where IDT is at */
   lidt((void*)Global_IDT, Global_IDT_size);

   /* Remap the PIC */
   PIC_remap(MASTER_PIC_NEW_OFFSET, SLAVE_PIC_NEW_OFFSET);
}

void IRQ_handler(int irq_num, int err) {

   /* Check if irq_num is within bounds */
   /* Execute code associated with interrupt */
   irq_table[irq_num].handler(irq_num, err, irq_table[irq_num].arg);
}
