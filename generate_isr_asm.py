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

		if i == 8 or (i > 9 and i < 15) or i == 17 or i == 30:
			opened_file.write("    push rdi\n" +
			                  "    mov rdi, [rsp + 8]\n" +
			 			  	  "    push rsi\n" +
			  		  	      "    mov rsi, [rsp + 8]\n" +
			  		  		  "    mov [rsp + 16], rsi\n" +
			   	  			  "    mov rsi, [rsp]\n" +
				              "    mov [rsp + 8], rsi\n" +
			   	  			  "    mov rsp, 8\n" +
				              "    mov rsi, rdi\n" +
				              "    mov rdi, " + str(i) + "\n" +
				              "    jmp common_irq_handler + 1\n\n")
			continue
		opened_file.write("    push rdi\n" +
				          "    mov rdi, " + str(i) + "\n" +
				          "    jmp common_irq_handler\n\n")

	opened_file.close()


'''
isr_wrappers 8, 10-14, 17, 30

isr_wrapper14:
    push rdi    mov rdi, [rsp + 8]
    push rsi    mov rsi, [rsp + 8]
    mov [rsp + 16], rsi
    mov rsi, [rsp]
    mov [rsp + 8], rsi
    add rsp, 8
    mov rsi, rdi
    mov rdi, [WRAPPER # (14)]
    jmp common_irq_handler + 1
'''

if __name__ == "__main__":
        if 1 == len(sys.argv):
		print "Usage: python generate_irq_asm.py < output_file_name >"
	else:
		generate_irq_asm_file(sys.argv[1])
