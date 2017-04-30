/*
 * interrupts.c - Contains implementations of
 * interrupt functions.
 * TODO:
 * - TSS for each interrupt
 * - Handle interrupts with errors
 */
#include "init_IDT_entries.h"
#include "interrupts.h"
#include "PIC.h"
#include "../lib/so_stdio.h"
#include "../lib/so_string.h"
#include "../helpers/ioaccess.h"
#include "keyboard.h"



/* Prototypes */
void init_interrupt_environment(void);
void IRQ_handler(int irq_num, int err);
static void init_irq_table(void);



/* GLOBALS */

/* IDT Table */
Interrupt_Descriptor Global_IDT[IDT_SIZE];

/* Interrupt Table */
static struct {
   void *arg;
   irq_handler_t handler;
} irq_table[IDT_SIZE];



/*
 * Sets up IDT and tells CPU where it's at.
 *  + Disable interrupts
 *  + Clear and Set IDT
 *  + LIDT to tell cpu where IDT is
 *  + Remap PIC
 *  + Set/Clear interrupt lines
 *  + init irq_handler
 *  + Enable interrupts
 *  + Set and Clear desirable interrupt lines
 */
void init_interrupt_environment() {
   size_t Global_IDT_size;
   Global_IDT_size = sizeof(Interrupt_Descriptor) * IDT_SIZE;

   memset((void*)Global_IDT, 0, Global_IDT_size);

   init_IDT();

   lidt((void*)Global_IDT, Global_IDT_size);

   PIC_remap(MASTER_PIC_NEW_OFFSET, SLAVE_PIC_NEW_OFFSET);

   for (int i = 0; i < IDT_SIZE; i++)
      PIC_set_mask(i);

   init_irq_table();

   printk(" Interrupts"); /* Signify end of init intr env*/
}

/* Func for testing irq_table c func entries */
static void implement_handler_code(int irq_num, int err, void *arg) {
  keyboard_interrupt_scancode();
}

static void init_irq_table() {
   for (int i = 0; i < IDT_SIZE; i++) {
      irq_table[i].arg = NULL;
      irq_table[i].handler = implement_handler_code;
   }
}

/* Takes CPU to the associated irq_num in irq_table */
/*
 * + Check if irq_num is within bounds
 * + Execute c function
 * + Get relative irq_num minusing offset
 * + Send EOI
 */
void IRQ_handler(int irq_num, int err) {

/* Debugging */
//   printk("irq#: %d.\n", irq_num);

   if (irq_num <= 0x2F && irq_num >= 0x20) {
      irq_table[irq_num].handler(irq_num, err, irq_table[irq_num].arg);
   }

   irq_num -= MASTER_PIC_NEW_OFFSET;

   PIC_sendEOI(irq_num);
}

/* Set handler for a specific line */
void IRQ_set_handler(int irq_num, irq_handler_t handler, void *arg) {
   irq_table[irq_num].arg = arg;
   irq_table[irq_num].handler = handler;
   PIC_clear_mask(irq_num - MASTER_PIC_NEW_OFFSET);
}
