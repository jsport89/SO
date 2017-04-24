#!/usr/bin/python

import sys
IRQ_VECTORS = 256

def generate_irq_init_files(file_name_path):
        header_file_name = file_name_path + ".h"
	header_file = open(header_file_name, "w")
	c_file_name = file_name_path + ".c"
	c_file = open(c_file_name, "w")

	# HEADER FILE
        
        header_file.write("#ifndef INIT_IDT_ENTRIES_H\n")
	header_file.write("#define INIT_IDT_ENTRIES_H\n\n")

	# print extern void* irq_wrapper_X
        for i in range(IRQ_VECTORS):
		header_file.write("extern void *isr_wrapper_" + str(i) + ";\n")

	# print out stub that inits Global_IDT (init entries irqwrap addr)
        header_file.write("\nvoid init_IDT(void);\n\n")
	header_file.write("#endif /* init_IDT_entries.h */")
	header_file.close()

	# C FILE

	c_file.write("#include \"init_IDT_entries.h\"\n")
        c_file.write("#include \"../lib/so_string.h\"\n")
	c_file.write("#include \"interrupts.h\"\n")
	c_file.write("#include <stdint-gcc.h>\n\n")

        # Prototypes 
        c_file.write("void init_IDT(void);\n\n")

	# Init OTHER fields 
	c_file.write("void init_IDT() {\n" +
                     "   memset((void*)Global_IDT, 0, sizeof(Interrupt_Descriptor) * 256);\n" + 
		     "   for (int i = 0; i < 256; i++) {\n" +
		# Assign Global_IDT[i].target_selector =
		     "      Global_IDT[i].dpl = 0;\n" +
		     "      Global_IDT[i].present = 1;\n" +
		     "      Global_IDT[i].type = 0xE;\n" +
		     "   }\n\n")
	
	# Init target offsets to isr_wrapper addresses
	c_file.write("   uint64_t isr_address;\n" +
		     "   uint32_t target_offset_3;\n" +
		     "   uint16_t target_offset_2;\n\n")
	for i in range(IRQ_VECTORS):
		c_file.write("   isr_address = (uint64_t)(isr_wrapper_" + str(i) + ");\n" +
			     "   target_offset_3 = isr_address >> 32;\n" +
			     "   Global_IDT[" + str(i) + "].target_offset_3 = target_offset_3;\n" +
			     "   target_offset_2 = isr_address >> 16;\n" +
			     "   Global_IDT[" + str(i) + "].target_offset_2 = target_offset_2 & 0xFFFF;\n" +
			     "   Global_IDT[" + str(i) + "].target_offset_1 = isr_address & 0xFFFF;\n\n")
	c_file.write("}")
	c_file.close()

'''
uint64_t isr_address = isr_wrapper_X;
uint32_t target_offset_3 = isr_address >> 32;
Global_IDT[i].target_offset_3 = target_offset_3;
uint16_t target_offset_2 = isr_address >> 48;
Global_IDT[i].target_offset_2 = target_offset_2 & 0xFFFF;
Global_IDT[i].target_offset_1 = isr_address & 0xFFFF;
'''


if __name__ == "__main__":
	if 1 == len(sys.argv):
		print "Usage: python generate_irq_init.py < c_file_name >"
	else:
		generate_irq_init_files(sys.argv[1])
