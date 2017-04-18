/*
 * so_stdio.c - contains implementations of
 * all so_stdio functions
 */
#include <stdarg.h>
#include <stdint-gcc.h>
#include "so_stdio.h"
#include "so_string.h"
#include "../drivers/vga_console.h"

#define FMT_SPEC '%'
#define TRUE 1
#define FALSE 0
#define NUM_BUFF_SIZE 32

char num_buff[NUM_BUFF_SIZE];

/* Prototypes */

void print_uchar(unsigned char);
void print_short(short);
void print_uint(unsigned int);

/* implemented */
void init_num_buff();
void print_char(char);
void print_str(const char *);
void print_long_long(long long);
void print_unsigned_long_long(unsigned long long);
void print_long_long_hex(unsigned long long);
void printk(const char *fmt, ...);

void init_num_buff() {
   for (int i = 0; i < NUM_BUFF_SIZE; i++)
      num_buff[i] = 0;
}

void print_str(const char *str) {
   VGA_display_str(str);
}

void print_char(char c) {
   VGA_display_char(c);
}

void print_long_long(long long num) {
   int i, ones_place_digit;
   char *position = num_buff + NUM_BUFF_SIZE - 1;
   int len = 0;
   int is_negative = FALSE;

   init_num_buff();

   /* Check if it's negative */
   if (num < 0) {
      is_negative = TRUE;
      num = num * -1;
   }

   /* Build Number */
   while (num >= 10) {
      ones_place_digit = num % 10;

      num /= 10;

     *position = ones_place_digit + '0';

      len++;
      position--;
   }

   *position = num + '0';
   len++;

   if (is_negative) {
      position--;
      *position = '-';
      len++;
   }

   /* print each char to display */
   for (i = 0; i < len; i++)
      print_char(*(position + i));

}

extern void print_unsigned_long_long(unsigned long long num) {
   int i, ones_place_digit;
   char *position = num_buff + NUM_BUFF_SIZE - 1;
   int len = 0;

   init_num_buff();

   /* Build Number */
   while (num >= 10) {
      ones_place_digit = num % 10;

      num /= 10;

     *position = ones_place_digit + '0';

      len++;
      position--;
   }

   *position = num + '0';
   len++;

   /* print each char to display */
   for (i = 0; i < len; i++)
      print_char(*(position + i));

}

/* Test cases */
/*
"something %d" , 1 => "something 1"
"something %d" , -1 => "something -1"
"something %d" , 0 => "something 0"
"something %d" , 10 => "something 10"
"something %d" , -10 => "something -10"
 */

void print_long_long_hex(unsigned long long num) {
   int i, digit;
   char *position = num_buff + NUM_BUFF_SIZE - 1;
   int len = 0;
   const char hex_table[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                             '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
   init_num_buff();

   /* Build hex */
   while (num >= 16) {
      digit = num % 16;

      num /= 16;

      *position = hex_table[digit];

      len++;
      position--;
   }

   *position = hex_table[num];
   len++;
/* Remove */
   position--;
   *position = 'x';
   position--;
   *position = '0';
   len += 2;

   for (i = 0; i < len; i++)
      print_char(*(position + i));
}

/* Test cases */
/*
0 => 0x0
1 => 0x1
10 => 0xa
17 => 0x11
32 => 0x20


 */

/*
 * Sends a given string to vga_buff
 * with given format specifiers
 */
/*
 %u %x %p %h[dux] %l[dux] %q[dux] %s %c %% %d
*/
void printk(const char *fmt, ...) {
   int i;
   va_list ap;
   va_start(ap, fmt);

   for (i = 0; i < strlen(fmt); i++) {

      if (FMT_SPEC == fmt[i]) {
         i++;
         switch(fmt[i]) {
            case 'c' :
               print_char(va_arg(ap, int));
               break;

            case 's' :
               print_str(va_arg(ap, const char *));
               break;

            case 'd' :
               print_long_long((long long)va_arg(ap, int));
               break;

            case 'u' :
               print_long_long((long long)va_arg(ap, unsigned int));
               break;

            case 'x' :
               print_long_long_hex((long long)va_arg(ap, unsigned int));
               break;

            case 'p' :
               print_long_long_hex((long long)va_arg(ap, uint64_t));
               break;

            case 'h' :
               print_long_long((long long)va_arg(ap, int));
               break;

            case 'l' :
               i++;
               switch(fmt[i]) {
                  case 'd' :
                     print_long_long((long long)va_arg(ap, long int));
                     break;
                  case 'u' :
                     print_unsigned_long_long((unsigned long long)va_arg(ap,  long unsigned int));
                     break;
                  case 'x' :
                     print_long_long_hex((unsigned long long)va_arg(ap, long unsigned int));
                     break;
               }
               break;

            case 'q' :
               i++;
               switch(fmt[i]) {
                  case 'd' :
                     print_long_long((long long)va_arg(ap, long long int));
                     break;
                  case 'u' :
                     print_unsigned_long_long((unsigned long long)va_arg(ap, long long unsigned));
                     break;
                  case 'x' :
                     print_long_long_hex((unsigned long long)va_arg(ap, long long unsigned int));
                     break;
               }
               break;

            case '%' :
               print_char('%');
               break;

            default :
               print_char('%');
               print_char('c');
               break;
         }
      }
      else
         print_char(fmt[i]);
   }

   va_end(ap);
}

/* Test Cases*/
/* "jules" => "jules" */
/* "jule%c",'z' => "julesz"*/
