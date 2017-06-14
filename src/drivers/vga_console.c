/* vga_console.c - contains the implementation of
 * of all vga_console driver functions.
 * TODO:
 * - '\n' is treated as '\r'
 * - Test scroll()
 * - Test VGA_display_char() cases
 * - #define background attributes (fix cursor colors)
 */
#include "vga_console.h"
#include "interrupts.h"
#include "../lib/so_string.h"
#include <stdint-gcc.h>

/* Screen Size Specs */
static unsigned short *vgaBuff = (unsigned short*)VGA_BASE;
const unsigned short SCREEN_MAX = WIDTH * HEIGHT;

/* Cursor Position in vgaBuff */
static int cursor = 0;

/* Prototypes */
void VGA_clear(void);
void VGA_display_char(char c);
void VGA_display_str(const char * str);
void scroll();
void VGA_display_attr_char(int x, int y, char c, int fg, int bg);
int VGA_row_count(void);
int VGA_col_count(void);

void VGA_display_attr_char(int x, int y, char c, int fg, int bg) {
   fg = fg << 8;
   bg = bg << 12;
   int char_attrbs = fg | bg;
   vgaBuff[y * WIDTH + x] =  char_attrbs | c;
}

int VGA_row_count(void) {
   return HEIGHT;
}

int VGA_col_count(void) {
   return WIDTH;
}

/* Clears entire screen */
void VGA_clear(void) {
   memset((void*)VGA_BASE, 0, SCREEN_MAX * 2);
   cursor = 0;
}

/* Outputs a char to cursor position */
void VGA_display_char(char c) {
   unsigned short char_attrbs = FONT;
   int enable_ints = INTS_OFF;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   /* Clear cursor */
   vgaBuff[cursor] = 0;

   if (c == '\n') {
      cursor += WIDTH - (cursor % WIDTH);
      if (cursor >= SCREEN_MAX) {
         scroll();
         cursor -= WIDTH;
      }
   }
   else if (c == '\b') {
      if (cursor == 0)
         return;
      cursor--;
      vgaBuff[cursor] = 0;
   }
   else {
      if (cursor == SCREEN_MAX) {
         scroll();
         cursor = SCREEN_MAX - WIDTH;
      }

      vgaBuff[cursor] = char_attrbs | c;
      cursor++;
   }
   /* Highlight cursor */
   vgaBuff[cursor] = CURSOR_ATTRBS;

   if (enable_ints) {
      STI
   }
}

/* Outputs a string starting from cursor position */
void VGA_display_str(const char *str) {
   while ('\0' != *str) {
      VGA_display_char(*str);
      str++;
   }
}

/* scoots everything in the window up by width (or to the left) */
void scroll() {

   /* Shift everything up by one row */
   for (unsigned short i = WIDTH; i < SCREEN_MAX; i++)
      vgaBuff[i - WIDTH] = vgaBuff[i];

   /* memset last (2*WIDTH) of SCREEN_MAX */
   memset((void*)((uint64_t)(VGA_BASE + (SCREEN_MAX * 2) - (WIDTH * 2))), 0, (WIDTH * 2));
}
