#include "tests.h"
void run_so_stdio_tests(void) {

   VGA_display_char('\n');

   char *d_test = "%d int test.";
   printk("%s 1 => %d.\n", d_test, 1);
   printk("%s -1 => %d.\n", d_test, -1);
   printk("%s 0 => %d.\n", d_test, 0);
   printk("%s 10 => %d.\n", d_test, 10);
   printk("%s -10 => %d.\n", d_test, -10);
   printk("%s 12345678 => %d.\n\n", d_test, 12345678);

   char *x_test = "%x hex test.";
   printk("%s 0 (0x0) => %x.\n", x_test, 0);
   printk("%s  1 (0x1) => %x.\n", x_test, 1);
   printk("%s 10 (0xa) => %x.\n", x_test, 10);
   printk("%s 17 (0x11) => %x.\n", x_test, 17);
   printk("%s  32 (0x20) => %x.\n", x_test, 32);
   printk("%s 987654 (0xf1206) => %x.\n", x_test, 987654);
   printk("%s 1234 (0x4d2) => %x.\n\n", x_test, 1234);

   char *u_test = "%u unsigned int test.";
   printk("%s 1 => %u.\n", u_test, 1);
   printk("%s -1 => %u.\n\n", u_test, -1);

   char *p_test = "%p pointer address test.";
   printk("%s *p_test's value address => %p.\n\n", p_test, (void*)p_test);

   char *l_test = "%ld %lu %lx tests.";
   long int arg1 = 1;
   long unsigned int arg2 = -1;
   long unsigned int arg4 = 1234;
   printk("%s %ld  %lu %lx.\n\n", l_test, arg1, arg2, arg4);
   printk("%%lu: %lu.\n\n", arg2);

}
