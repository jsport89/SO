/* Kernel uses ps2_poll_write to */
#include "ps2.h"

#define PS2_DATA 0x60
#define PS2_CMD 0x64
#define PS2_STATUS PS2_CMD
#define PS2_STATUS_OUTPUT 1
#define PS2_STATUS_INPUT (1 << 1)

static void ps2_poll_write(uint8_t c) {
   char status = inb(PS2_STATUS);

   while(!(status & PS2_STATUS_OUTPUT))
      status = inb(PS2_STATUS);

   outb(PS2_DATA, c);
}

static char ps2_poll_read(void) {
   char status = inb(PS2_STATUS);

   while (!(status & PS2_STATUS_OUTPUT))
      status = inb(PS2_STATUS);

   return inb(PS2_DATA);
}

void ps2_init(void) {
   /*
   1. Disable devices on both channel 1 and channel 2
   2. Read the PS/2 configuration byte (need current configuration to update
   only a subset of the bits). This is a two step process that involves polling.
   only a subset of the bits). This is a two step process that involves polling.
   only a subset of the bits). This is a two step process that involves polling.
   3. PS/2 data port is shared with device data port
   4. Write a value to control port to force PS/2 controller to write its status
   to data port
   5. Wait for data to become available
   6. Read data from data port
   7. Enable the clock on channel 1
   8. Enable interrupts on channel 1, assuming you want interrupts
   9. Enable channel 2 (as desired)
   10. Write the configuration byte back out to the PS/2 controller. This is a two
   step process that involves polling.
   11. Enable port 1
   12. Enable port 2 (as desired)
    */

   return;
}
