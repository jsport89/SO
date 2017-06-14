/*
 * interrupts.c - Contains implementations of
 * interrupt functions.
 * TODO:
 * - Put error handlers in different file.
 *    + Make sure you add the handler after initialization
 * - Handle interrupts with errors
 */
#include "init_IDT_entries.h"
#include "interrupts.h"
#include "PIC.h"
#include "../lib/so_stdio.h"
#include "../lib/so_string.h"
#include "../lib/types.h"
#include "../helpers/ioaccess.h"
#include "keyboard.h"
#include "tss.h"


/* Prototypes */
void init_interrupt_environment(void);
void IRQ_handler(int irq_num, int err);
static void init_irq_table(void);
void df_handler(int irq_num, int err, void *ar);
void gp_handler(int irq_num, int err, void *ar);
void pf_handler(int irq_num, int err, void *ar);


/* GLOBALS */

/* IDT Table */
Interrupt_Descriptor Global_IDT[IDT_SIZE];

/* Interrupt Table */
static struct {
   void *arg;
   irq_handler_t handler;
} irq_table[IDT_SIZE];

/* SYSCALL STUFF TO MOVE Syscall Table */
void execute_syscall(uint64_t syscall_num);
static struct {
   syscall_handler_t handler;
} syscall_table[SCT_SIZE];

void init_syscall_table() {
   for (int i = 0; i < SCT_SIZE; i++) {
      syscall_table[i].handler = NULL;
   }
}

void syscall_set_handler(int syscall_num, syscall_handler_t handler) {
   if (syscall_num <= SCT_SIZE && syscall_num >= 0) {
      syscall_table[syscall_num].handler = handler;
   }
   else {
      printk("INTERRUPTS: Bad syscall_num to set.\n");
      for(;;) {
        __asm__("hlt");
      }
   }
}
void execute_syscall(uint64_t syscall_num) {
   syscall_table[syscall_num].handler(0, 0, 0, 0, 0);
}

/*
 * Sets up IDT and tells CPU where it's at.
 *  + Disable interrupts
 *  + Clear and Set IDT
 *  + LIDT to tell cpu where IDT is
 *  + Remap PIC
 *  + Set interrupt lines
 *  + Clear error interrupt lines
 *  + init irq_table
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

   PIC_clear_mask(8);  // DF
   PIC_clear_mask(13); // GP
   PIC_clear_mask(14); // PF

   init_irq_table();

/* SYSCALL STUFF TO MOVE */
   init_syscall_table();

   /* Set irq_handlers for exceptions */
   IRQ_set_handler(DF_GLOBAL_IDT_INDEX, df_handler, NULL);
   IRQ_set_handler(GP_GLOBAL_IDT_INDEX, gp_handler, NULL);
   //IRQ_set_handler(PF_GLOBAL_IDT_INDEX, pf_handler, NULL);
   /*
    * DF - 8
    * GP - 13
    * PF - 14
    * arrays of 4096 bytes, set to end addresses
    */
   Global_IDT[DF_GLOBAL_IDT_INDEX].isti = 1;
   Global_IDT[GP_GLOBAL_IDT_INDEX].isti = 2;
   Global_IDT[PF_GLOBAL_IDT_INDEX].isti = 4;

   printk(" Interrupts."); /* Signify end of init intr env*/
}

/* Func for testing irq_table c func entries */
static void implement_handler_code(int irq_num, int err, void *arg) {
 /* keyboard_interrupt_scancode(); */
   printk("Implement handler code for this interrupt line: %d.\n", irq_num);
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

/* Debugging
   register intptr_t stack_pointer asm("rsp");
   printk("\nInterrupt stack address: %x.\n", stack_pointer);
   printk("irq#: %d.\n", irq_num);
 */
   if (irq_num <= 255 && irq_num >= 0) {
      irq_table[irq_num].handler(irq_num, err, irq_table[irq_num].arg);
   }

   if (irq_num >= MASTER_PIC_NEW_OFFSET)
      irq_num -= MASTER_PIC_NEW_OFFSET;

   PIC_sendEOI(irq_num);

}

/* Set handler for a specific line */
void IRQ_set_handler(int irq_num, irq_handler_t handler, void *arg) {
   irq_table[irq_num].arg = arg;
   irq_table[irq_num].handler = handler;
   PIC_clear_mask(irq_num - MASTER_PIC_NEW_OFFSET);
}

void df_handler(int irq_num, int err, void *ar) {
   register intptr_t stack_pointer asm("rsp");
   printk("\n\nDF stack address: %x.\n", (unsigned int)stack_pointer);
}

void gp_handler(int irq_num, int err, void *ar) {
   register intptr_t stack_pointer asm("rsp");
   printk("\n\nGP stack address: %x.\n", (unsigned int)stack_pointer);
   uint64_t v_add_causing_gpf;
   uint64_t cr3_contents;
//   uint64_t rip_contents;
   __asm__("movq %%cr2, %0" : "=r"(v_add_causing_gpf));
   __asm__("movq %%cr3, %0" : "=r"(cr3_contents));
   //__asm__("movq %%rip, %0" : "=r"(rip_contents));


   printk("KERN_INFO_PF: cr2 - %lu.\n", v_add_causing_gpf);
   printk("KERN_INFO_PF: cr3 - %lu.\n", cr3_contents);
   printk("KERN_INFO_PF: error - %d.\n", err);
   printk("KERN_INFO_PF: irq_num - %d.\n", irq_num);


   for(;;) {
     __asm__("hlt");
   }
}
