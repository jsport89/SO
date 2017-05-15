/*
 * serial_output.c - contains implementations of functions to Interface
 * with serial device.
 * TODO:
 * + Do something with STATE flag (idle)?
 * + Implement SER_write_char
 */

#include "serial_output.h"
#include "interrupts.h"
#include "vga_console.h"
#include "PIC.h"
#include "../lib/so_string.h"
#include "../lib/so_stdio.h"
#include "../helpers/ioaccess.h"

#define PORT 0x3F8   /* COM1 */
#define SERIAL_IRQ_NUMBER 36
#define LINE 0x6
#define TX 0x2
#define IDLE 0
#define BUSY 1
#define SUCCESS 1
#define FAILED 0


/* Prototypes */
extern void SER_init(void);
extern int SER_write(const char *buff, int len);
extern int SER_write_char(const char c);
extern int is_hardware_buff_empty(void);
static void init_state(struct State *state);
static void consumer_next(struct State *state);
static int producer_add_char(char to_add, struct State *state);
static void init_hardware(void);
static void serial_handler_code(int irq_num, int err, void *arg);
static void hardware_write(uint8_t c);
static int is_serial_buff_empty(void);

/* Global variables */
static struct State UART_meta;

/*
 * Initializes serial driver
 * + Create state structure to hold UART data
 * + Allocate state statically inside one function
 * + Init structure
 * + Init hardware (set communic type, no parity, stop bit, enable interrupts on TX)
 * + Register an interrupt handler for the correct IRQ number
 * + Unmask the serial IRQ number
 */
void SER_init() {
   init_state(&UART_meta);

   init_hardware();

   IRQ_set_handler(SERIAL_IRQ_NUMBER, serial_handler_code, &UART_meta);

   printk(" Serial.");
}

int SER_write_char(const char c) {
   char char_to_print = c;
   int status;
   int enable_ints = INTS_OFF;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   if (is_hardware_buff_empty() && is_serial_buff_empty()) {
      hardware_write(c);
      status = SUCCESS;
   }
   else if(!(UART_meta.tail == UART_meta.head - 1) &&
       !(UART_meta.head == &UART_meta.buff[0] &&
       UART_meta.tail == &UART_meta.buff[BUFF_SIZE-1])) {
      status = producer_add_char(char_to_print, &UART_meta);
      consumer_next(&UART_meta);
   }

   if (enable_ints) {
      STI
   }

   return status;
}

/*
 * + Disable interrupts as appropriate
 * + Ensure the buffer has capacity, if so
 *   – Add item to buffer
 *   – Increment producer buffer pointer
 *   – repeat until buffer is full or all items have been added
 *   – call function to initiate hardware write
 * + Enable interrupts as appropriate
 */
int SER_write(const char *buff, int len) {
   int enable_ints = INTS_OFF;
   const char *to_write = buff;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   while(len) {
      SER_write_char(*to_write);
      to_write++;
      len--;
   }

   if (enable_ints)
      STI

   return SUCCESS;
}

/*
 * + Disable interrupts
 * + Read hardware IIR register for interrupt cause
 *   - If LINE, read LSR to clear interrupt
 *   - If TX, set serial to idle state AND call func to initiate hardware write
 * + Acknowledge the interrupts with the PIC
 * + Enable interrupts
 */
static void serial_handler_code(int irq_num, int err, void *arg) {
   int enable_ints = INTS_OFF;
   unsigned char status;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   status = inb(PORT + 2);

   if (LINE == (status & LINE)) {
      inb(PORT + 5); // Clear interrupt
   }
   else if (status & TX) {
      UART_meta.busy_flag = IDLE;
      consumer_next(&UART_meta);
      /*
       * If serial buffer is empty, check hardware buffer.
       *    If hardware buffer is empty
       *       Write to serial device port
       *       return
       * else
       *   Get char from serial buffer
       */
      /*
      if (is_serial_buff_empty() && is_hardware_buff_empty()) {
         hardware_write('a');
         UART_meta.busy_flag = BUSY;

         return;

      }

      if (!(is_serial_buff_empty()) && !(is_hardware_buff_empty())) {
         producer_add_char();
      }
      consumer_next(&UART_meta);
      */
   }

   if (enable_ints)
      STI
}

static void init_hardware() {
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

/* Consumer Producer functions */
static void init_state(struct State *state) {
   state->head = &state->buff[0];
   state->tail = &state->buff[0];
   memset((void*)state, 0, BUFF_SIZE);
}

/* hardware write outb to PORT */
static void hardware_write(uint8_t c) {
   if (UART_meta.busy_flag == BUSY) {
      while (is_hardware_buff_empty() == 0);
      UART_meta.busy_flag = IDLE;
   }

   outb(PORT, c);
   UART_meta.busy_flag = BUSY;
}

/* Write a char from serial buffer to hardware. or don't */
static void consumer_next(struct State *state) {
   /* Empty buffer */
   if (state->head == state->tail)
      return;

   /* hardware write */
   hardware_write(*state->head++);

   /* reset head */
   if (state->head >= &state->buff[BUFF_SIZE])
      state->head = &state->buff[0];
}

/* Add char to serial buffer */
static int producer_add_char(char to_add, struct State *state) {

   /* buffer is full*/
   if (state->tail == state->head - 1 ||
      (state->head == &state->buff[0] &&
       state->tail == &state->buff[BUFF_SIZE-1]) ) {
      return FAILED;
   }

   *state->tail++ = to_add;

   if (state->tail >= &state->buff[BUFF_SIZE])
      state->tail = &state->buff[0];

   return SUCCESS;
}

int is_hardware_buff_empty() {
   return inb(PORT + 5) & 0x20;
}

static int is_serial_buff_empty() {
   return UART_meta.head == UART_meta.tail;
}
