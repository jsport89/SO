/* vga_console.h - header that includes all vga_driver functions */
#ifndef VGA_CONSOLE_H
#define VGA_CONSOLE_H

#define VGA_BASE 0xb8000
#define WIDTH 80  /* Pixels? */
#define HEIGHT 25
#define FONT 10 << 8
#define CURSOR_ATTRBS 160 << 8

extern void VGA_clear(void);
extern void VGA_display_char(char);
extern void VGA_display_str(const char *);

void VGA_display_attr_char(int x, int y, char c, int fg, int bg);
int VGA_row_count(void);
int VGA_col_count(void);

#endif /* vga_console.h */
