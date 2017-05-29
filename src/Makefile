CC = /home/kamdori/opt/cross/bin/x86_64-elf-gcc
CFLAGS = -c -g -Wall
build_objs_dir = arch/x86_64/lib_objs

all:
	@$(CC) $(CFLAGS) -o lib/so_string.o  lib/so_string.c
	@$(CC) $(CFLAGS) -o lib/so_stdio.o lib/so_stdio.c
	@$(CC) $(CFLAGS) -o lib/so_kmalloc.o lib/so_kmalloc.c
	@$(CC) $(CFLAGS) -o drivers/vga_console.o  drivers/vga_console.c
	@$(CC) $(CFLAGS) -o drivers/ps2.o drivers/ps2.c
	@$(CC) $(CFLAGS) -o drivers/keyboard.o drivers/keyboard.c
	@$(CC) $(CFLAGS) -o drivers/init_drivers.o drivers/init_drivers.c
	@$(CC) $(CFLAGS) -o drivers/serial_output.o drivers/serial_output.c
	@$(CC) $(CFLAGS) -o drivers/interrupts.o drivers/interrupts.c
	@$(CC) $(CFLAGS) -o drivers/PIC.o drivers/PIC.c
	@$(CC) $(CFLAGS) -o drivers/init_IDT_entries.o drivers/init_IDT_entries.c
	@$(CC) $(CFLAGS) -o drivers/tss.o drivers/tss.c
	@$(CC) $(CFLAGS) -o helpers/ioaccess.o helpers/ioaccess.c
	@$(CC) $(CFLAGS) -o tests/so_stdio_tests.o tests/so_stdio_tests.c
	@$(CC) $(CFLAGS) -o tests/so_string_tests.o tests/so_string_tests.c
	@$(CC) $(CFLAGS) -o tests/vga_console_tests.o tests/vga_console_tests.c
	@$(CC) $(CFLAGS) -o sys/page_alloc.o sys/page_alloc.c
	@$(CC) $(CFLAGS) -o sys/virtual_page_alloc.o sys/virtual_page_alloc.c
	@$(CC) $(CFLAGS) -o kernel.o kernel.c -mno-red-zone

clean:
	-rm *.o
	-rm lib/*.o
	-rm drivers/*.o
	-rm sys/*.o
	-rm helpers/*.o
	-rm tests/*.o
