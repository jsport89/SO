/*
 * so_stdio.h - contains all standard input output
 * functions for the Somewhat Operating Operating System
 */
#ifndef SO_STDIO_H
#define SO_STDIO_H

/* Functions */
extern void print_uchar(unsigned char);
extern void print_short(short);
extern void print_uint(unsigned int);

extern void print_char(char);
extern void print_str(const char *);
extern void print_long_long(long long); /* Prints shorts, ints, long, long long*/
extern void print_unsigned_long_long(unsigned long long); /* Prints unsigned long, unsigned long long*/
extern void print_long_long_hex(unsigned long long);
extern void printk(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

#endif /* so_stdio.h */
