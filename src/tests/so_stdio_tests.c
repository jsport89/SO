#include "tests.h"
#include "../lib/so_stdio.h"
#include "../drivers/vga_console.h"
#include <stdint-gcc.h>


void run_so_stdio_tests(void) {

   VGA_display_char('\n');

   char *d_test = "%d int test.";
   printk("%s 1 => %d.\n", d_test, 1);
   printk("%s -1 => %d.\n", d_test, -1);
   printk("%s MAX => %d.\n", d_test, INT32_MAX);
   printk("%s MIN => %d.\n", d_test, INT32_MIN);

   char *x_test = "%x hex test.";
   printk("%s 0 (0x0) => %x.\n", x_test, 0);
   printk("%s  1 (0x1) => %x.\n", x_test, 1);
   printk("%s 10 (0xa) => %x.\n", x_test, 10);
   printk("%s 17 (0x11) => %x.\n", x_test, 17);
   printk("%s  32 (0x20) => %x.\n", x_test, 32);
   printk("%s 987654 (0xf1206) => %x.\n", x_test, 987654);
   printk("%s 1234 (0x4d2) => %x.\n", x_test, 1234);

   char *u_test = "%u unsigned int test.";
   printk("%s 1 => %u.\n", u_test, 1);
   printk("%s -1 => %u.\n", u_test, -1);

   char *p_test = "%p pointer address test.";
   printk("%s *p_test's value address => %p.\n", p_test, (void*)p_test);

   printk("h[dux] Tests:\n");
   short hd_test_1 = INT16_MAX;
   short hd_test_2 = INT16_MIN;
   unsigned short hu_test_1 = UINT16_MAX;
   unsigned short hu_test_2 = 1;
   printk("hd: %hd %hd.\n", hd_test_1, hd_test_2);
   printk("hu: %hu %hu .\n", hu_test_1, hu_test_2);
   printk("hx: %hx %hx.\n", hu_test_1, hu_test_2);

   printk("l[dux] Tests:\n");
   long int ld_test_1 = INT64_MAX;
   long int ld_test_2 = INT64_MIN;
   long unsigned int lu_test_1 = UINT64_MAX;
   long unsigned int lu_test_2 = 1;
   printk("ld: %ld %ld.\n", ld_test_1, ld_test_2);
   printk("lu: %lu %lu .\n", lu_test_1, lu_test_2);
   printk("lx: %lx %lx.\n", lu_test_1, lu_test_2);

   printk("q[dux] Tests:\n");
   long long int qd_test_1 = INT64_MAX;
   long long int qd_test_2 = INT64_MIN;
   long long unsigned int qu_test_1 = UINT64_MAX;
   long long unsigned int qu_test_2 = 1;
   printk("qd: %qd %qd.\n", qd_test_1, qd_test_2);
   printk("qu: %qu %qu .\n",qu_test_1, qu_test_2);
   printk("qx: %qx %qx.\n", qu_test_1, qu_test_2);

}
