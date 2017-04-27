#!/usr/bin/python

import sys
IRQ_VECTORS = 256


def generate_irq_asm_file(file_out_name):
	opened_file = open(file_out_name, "w")

	# global isr_wrapper funcs
	for i in range(IRQ_VECTORS):
		opened_file.write("global isr_wrapper_" + str(i) + "\n")

        opened_file.write("\nextern IRQ_handler\n")

	opened_file.write("\nsection .text\n")

	opened_file.write("\ncommon_irq_handler:\n" +
                      "    push rsi\n" +
			          "    push rdx\n" +
			          "    push rcx\n" +
			          "    push r8\n" +
                      "    push r9\n" +
                      "    call IRQ_handler\n" +
			          "    pop r9\n" +
			          "    pop r8\n" +
                      "    pop rcx\n" +
                      "    pop rdx\n" +
                      "    pop rsi\n" +
                      "    pop rdi\n" +
			          "    iretq\n\n")

	for i in range(IRQ_VECTORS):
		opened_file.write("isr_wrapper_" + str(i) + ":\n")
		opened_file.write("    push rdi\n" +
				          "    mov rdi, " + str(i) + "\n" +
				          "    jmp common_irq_handler\n\n") 

        opened_file.close()


if __name__ == "__main__":
        if 1 == len(sys.argv):
		print "Usage: python generate_irq_asm.py < output_file_name >"
	else:
		generate_irq_asm_file(sys.argv[1])
