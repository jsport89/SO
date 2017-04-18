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

void write_to_cmd_port(uint8_t msg) {
   ps2_poll_write_cmd(msg);
}

void write_to_data_port(uint8_t msg) {
   ps2_poll_write_data(msg);
}

char read_from_data_port(void) {
   return ps2_poll_read();
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

void ps2_init(void) {
   uint8_t command = 0;
   uint8_t response = 0;
   uint8_t config = 17; /* 51; */

   /* Disable devices on channel 1 & 2 */
   command = 0xAD;
   ps2_poll_write_cmd(command);

   command = 0xA7;
   ps2_poll_write_cmd(command);

   /* Flush output buff */
   response = ps2_poll_read();

   /*
    * Read PS/2 config byte:
    * + Write to control port to get status in data port
    * + Read config from data port
    */

   command = 0x20;
   ps2_poll_write_cmd(command);

   response = ps2_poll_read();

   /* Enable the clock and interrupts on channel 1 & 2 */

   /* Write next byte to config byte */
   ps2_poll_write_cmd(0x60);
   config = response | config;
   ps2_poll_write_data(config);

   /* Self Test (returns 0x55)*/
   ps2_poll_write_cmd(0xAA);
   response = ps2_poll_read();

/* DEBUGGING */
   printk("Response if config byte was set (0x55 = passed): %x.\n", (unsigned int)response);

   /* Interface test */
   ps2_poll_write_cmd(0xAB);
   response = ps2_poll_read();

/* DEBUGGING */
   printk("Interface test port1 (0x00 = passed): %x.\n", (unsigned int)response);

/*
   ps2_poll_write_cmd(0xA9);
   response = ps2_poll_read();
   printk("Interface test port2 (0x00 = passed): %x.\n", (unsigned int)response);
*/

   /* Enable devices on ports 1 & 2 */
   command = 0xAE;
    ps2_poll_write_cmd(command);
/*
   command = 0xA8;
   ps2_poll_write_cmd(command);
 */
   return;
}
