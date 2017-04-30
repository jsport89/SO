/*
 * keyboard.c - contains implementations of
 * keyboard driver functions.
 */
#include "keyboard.h"
#include "ps2.h"
#include "vga_console.h"
#include "interrupts.h"
#include "../lib/so_stdio.h"
#include "../lib/so_string.h"
#define KEYBOARD_IRQ_NUM 33
#define SCANCODE_TABLE_SIZE 256
#define SELF_TEST_PASSED 0xAA
#define ACK 0xFA

/*
 * TODO:
 * - Modifier keys
 * - l-ctr
 * - l-shft
 * - r-shft
 * - l-alt
 */
char scancode[SCANCODE_TABLE_SIZE] = {
0, 0, '1', '2', '3' , '4' , '5', '6', '7' , '8', '9', '0', '-', '=' , '\b', '\t',
'q', 'w', 'e', 'r', 't', 'y' , 'u' , 'i', 'o', 'p' , '[', ']', '\n', 0/*l-ctr*/ , 'a', 's',
'd', 'f', 'g', 'h', 'j', 'k' , 'l' , ';', '\'', '`' , 0/* l-shft*/, '\\', 'z', 'x', 'c' ,'v',
'b', 'n', 'm', ',', '.', '/', 0 /* r-shft */ , 0 /* * */, 0 /* l-alt */, ' ', 0 , 0, 0, 0, 0 ,0,
0, 0, 0, 0, 0, 0, 0 , 0 , 0, 0, 0 , 0, 0, 0, 0 ,0,
0, 0, 0, 0, 0, 0, 0 , 0 , 0, 0, 0 , 0, 0, 0, 0 ,0,
0, 0, 0, 0, 0, 0, 0 , 0 , 0, 0, 0 , 0, 0, 0, 0 ,0,
0, 0, 0, 0, 0, 0, 0 , 0 , 0, 0, 0 , 0, 0, 0, 0 ,0
};

/* Prototypes */
void keyboard_init(void);
void keyboard_poll_scancodes(void);
void keyboard_interrupt_scancode(void);
char get_scancode();
char get_char();
static void keyboard_handler_code(int irq_num, int err, void *arg);

static void keyboard_handler_code(int irq_num, int err, void *arg) {
   keyboard_interrupt_scancode();
}

char get_scancode() {
   return read_from_data_port();
}

char get_char() {
   uint8_t offset;
   char to_print;

   offset = get_scancode();
   to_print = scancode[offset];

   return to_print;
}

/*
 * Prints a char from the PS2 output buffer
 * to the VGA and serial output buffer
 */
void keyboard_interrupt_scancode() {
   char char_to_print = get_char();

   if (char_to_print != 0)
      printk("%c", char_to_print);
   if (char_to_print == '\n')
      printk(">> ");
}

/*
 * + Reset keyboard
 * + Set scan codes
 * + Enable Keyboard
 */
void keyboard_init(){
   uint8_t response;
   uint8_t command = 0xFF; /* Reset device */

      write_to_data_port(command);
      response = read_from_data_port();

      if (response != ACK)
         printk("Keyboard init: Failed reset test. Response: %x.\n", (unsigned int)response);

      response = read_from_data_port();

      if (response != SELF_TEST_PASSED)
         printk("Keyboard init: Failed reset test.  Response %x\n", (unsigned int)response);

      command = 0xF0;
      write_to_data_port(command);

      response = read_from_data_port();

      if (response != ACK)
         printk("Keyboard init: Failed scan set.  Response: %x.\n", (unsigned int)response);

      command = 0x01;
      write_to_data_port(command);

      response = read_from_data_port();

      if (response != ACK)
         printk("Keyboard init: Failed scan set sub.  Response: %x.\n", (unsigned int)response);

      command = 0xF4;
      write_to_data_port(command);

      response = read_from_data_port();
      if (response != ACK)
         printk("Keyboard init: Failed enable.  Response: %x.\n", (unsigned int)response);

      IRQ_set_handler(KEYBOARD_IRQ_NUM, keyboard_handler_code, NULL);

    printk(" Keyboard");
}

/* Old polling code */
char poll_char() {
   uint8_t offset;
   char to_print;

   offset = read_poll_data_port();
   to_print = scancode[offset];

   return to_print;
}

/* Old code */
void keyboard_poll_scancodes() {

   printk(">> ");
   /* Get ascii value from lookup table */
   while(1) {
      char to_print = poll_char();

         if (to_print != 0)
            printk("%c", to_print);
   }
}
