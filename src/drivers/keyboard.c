/*
 * keyboard.c - contains implementations of
 * keyboard driver functions.
 */
#include "keyboard.h"
#include "ps2.h"
#include "../lib/so_stdio.h"
#include "../lib/so_string.h"
#define SCANCODE_TABLE_SIZE 256

/*
 * TODO:
 * - backspace
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
static void keyboard_init(void);
void keyboard_poll_scancodes(void);
char get_scancode();
char get_char();

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

void keyboard_poll_scancodes() {

   keyboard_init();

   /* Get ascii value from lookup table */
   while(1) {
      char to_print = get_char();

         if (to_print != 0)
            printk("%c", to_print);
   }
}

static void keyboard_init(){
   uint8_t response;
   uint8_t command = 0xFF; /* Reset device */

   /* init ps2 controller */
      ps2_init();

   /* reset keyboard */
      write_to_data_port(command);
      response = read_from_data_port();

   /* DEBUGGING */
      printk("Rest resp: %x\n", (unsigned int)response);

      response = read_from_data_port();

   /* DEBUGGING */
      printk("Rest resp: %x\n", (unsigned int)response);

   /* Set scan codes*/
      command = 0xF0;
      write_to_data_port(command);

   /* DEBUGGING */
      response = read_from_data_port();
      printk("Scan cmd resp: %x\n", (unsigned int)response);

      command = 0x01;
      write_to_data_port(command);

   /* DEBUGGING */
      response = read_from_data_port();
      printk("Scan sub cmd resp: %x\n", (unsigned int)response);

   /* enable keyboard */
      command = 0xF4;
      write_to_data_port(command);

   /* DEBUGGING */
      response = read_from_data_port();
      printk("Enable keyboard cmd resp: %x\n", (unsigned int)response);
}
