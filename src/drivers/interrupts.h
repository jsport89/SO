#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <stdint-gcc.h>

#define IDT_SIZE 256
#define CLI asm("cli" : : );
#define STI asm("sti" : : );
#define INTS_OFF 0
#define INTS_ON 1
#define MASTER_PIC_NEW_OFFSET 0x20
#define SLAVE_PIC_NEW_OFFSET 0x28

/* Typedefs */
typedef struct {
   uint16_t target_offset_1;
   uint16_t target_selector;
   uint16_t isti : 3; /* interrupt_stack_table_index */
   uint16_t reserved_1 : 5;
   uint16_t type : 4; /* Interrupt OR Trap? */
   uint16_t zero : 1;
   uint16_t dpl : 2; /* descriptor_privilege_level */
   uint16_t present : 1;
   uint16_t target_offset_2;
   uint32_t target_offset_3;
   uint32_t reserved_2;
}__attribute__((packed)) Interrupt_Descriptor;

typedef void (*irq_handler_t)(int, int, void*);


/* Globals */
extern Interrupt_Descriptor Global_IDT[IDT_SIZE];

/* Functions */
extern void IRQ_handler(int irq_num, int err);
extern void IRQ_set_handler(int irq, irq_handler_t handler, void *arg);
void init_interrupt_environment(void);

/* Tell cpu where IDT is */
static inline void lidt(void* base, uint16_t size)
{   // This function works in 32 and 64bit mode
    struct {
        uint16_t length;
        void*    base;
    } __attribute__((packed)) IDTR = { size, base };

    asm ( "lidt %0" : : "m"(IDTR) );  // let the compiler choose an addressing mode
}

/* Checks if interrupts are enabled */
static inline int are_interrupts_enabled()
{
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}



/* asm("int $0x21");*/
#endif /* interrupts.h */
