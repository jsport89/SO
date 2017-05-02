/*
 * ps2.c - contains implemented functions pertinent to
 * the PS/2 controller
 */
#include "ps2.h"
#include "../lib/so_stdio.h"

/* Prototypes */
static void ps2_poll_write_cmd(uint8_t c);
static void ps2_poll_write_data(uint8_t c);
static char ps2_poll_read(void);
void ps2_init(void);
void write_to_cmd_port(uint8_t msg);
void write_to_data_port(uint8_t msg);
char read_from_data_port(void);
char read_poll_data_port(void);


void write_to_cmd_port(uint8_t msg) {
   ps2_poll_write_cmd(msg);
}

void write_to_data_port(uint8_t msg) {
   ps2_poll_write_data(msg);
}

/* Wrapper for keyboard_poll_scancodes */
char read_poll_data_port(void) {
   return ps2_poll_read();
}

char read_from_data_port(void) {
   return inb(PS2_DATA);
}

static void ps2_poll_write_data(uint8_t c) {
   char status = inb(PS2_STATUS);

   while(status & PS2_STATUS_INPUT)
      status = inb(PS2_STATUS);

   outb(PS2_DATA, c);
}

static void ps2_poll_write_cmd(uint8_t c) {
   char status = inb(PS2_STATUS);

   while(status & PS2_STATUS_INPUT)
      status = inb(PS2_STATUS);

   outb(PS2_CMD, c);
}

static char ps2_poll_read(void) {
   char status = inb(PS2_STATUS);

   while (!(status & PS2_STATUS_OUTPUT))
      status = inb(PS2_STATUS);

   return inb(PS2_DATA);
}

/*
 * + Disable devices on channel 1 & 2
 * + Flush output buff
 * + Read/Set config byte
 * + Self test
 * + Interface test
 * + Enable clock and interrupts on channel 1
 * + Enable Device on Port 1
 */
void ps2_init(void) {
   uint8_t command = 0;
   uint8_t response = 0;
   uint8_t config = 17; /* 51; */

   command = 0xAD;
   ps2_poll_write_cmd(command);

   command = 0xA7;
   ps2_poll_write_cmd(command);

   response = ps2_poll_read(); /* Flush */

   /*
    * Read PS/2 config byte:
    * + Write to control port to get status in data port
    * + Read config from data port
    */

   command = 0x20;
   ps2_poll_write_cmd(command);

   response = ps2_poll_read();

   ps2_poll_write_cmd(0x60);
   config = response | config;
   ps2_poll_write_data(config);

   ps2_poll_write_cmd(0xAA);
   response = ps2_poll_read();

   if (response != 0x55)
      printk("\nPS2: Failed self test. Response: %x.\n", (unsigned int)response);

   ps2_poll_write_cmd(0xAB);
   response = ps2_poll_read();

   if (response != 0x00)
      printk("\nPS2: Failed interface test. Response: %x.\n", (unsigned int)response);

   /* Enable devices on ports 1 & 2 */
   command = 0xAE;
   ps2_poll_write_cmd(command);

   printk(" PS/2.");
}
