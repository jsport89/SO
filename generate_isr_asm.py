#!/usr/bin/python

import sys
IRQ_VECTORS = 256

'''
"    push rsi\n" +
"    push rdx\n" +
"    push rcx\n" +
"    push r8\n" +
"    push r9\n" +
"    push rax\n" +
"    push rbx\n" +
"    push rsp\n" +
"    push rbp\n" +
"    call IRQ_handler\n" +
"    call context_switch\n\n")
"    pop rbp\n" +
"    pop rsp\n" +
"    pop rbx\n" +
"    pop rax\n" +
"    pop r9\n" +
"    pop r8\n" +
"    pop rcx\n" +
"    pop rdx\n" +
"    pop rsi\n" +
"    pop rdi\n" +
"    iretq\n\n")

("\ncommon_irq_handler:\n" +
					"    push rsi\n" +
					"    push rax\n" +
					"    push rbx\n" +
					"    push rcx\n" +
					"    push r8\n" +
					"    push r9\n" +
					"    push r10\n" +
					"    push r11\n" +
					"    push r12\n" +
					"    push r13\n" +
					"    push r14\n" +
					"    push r15\n" +
					"    push rbp\n" +
					"    call IRQ_handler\n" +
					"    jmp context_switch\n" +
					"    pop rbp\n" +
					"    pop r15\n" +
					"    pop r14\n" +
					"    pop r13\n" +
					"    pop r12\n" +
					"    pop r11\n" +
					"    pop r10\n" +
					"    pop r9\n" +
					"    pop r8\n" +
					"    pop rcx\n" +
					"    pop rbx\n" +
					"    pop rax\n" +
					"    pop rsi\n" +
					"    pop rdi\n" +
					"    iretq\n\n")

save_proc:
    mov rsi, [rsp + 112]
    mov [curr_proc], rsi
    mov rsi, [rsp + 120]
    mov [curr_proc + 8], rsi
    mov rsi, [rsp + 128]
    mov [curr_proc + 16], rsi
    mov rsi, [rsp + 136]
    mov [curr_proc + 24], rsi
    mov rsi, [rsp + 144]
    mov [curr_proc + 32], rsi

    pop qword [curr_proc + 148]
    pop qword [curr_proc + 136]
    pop qword [curr_proc + 128]
    pop qword [curr_proc + 120]
    pop qword [curr_proc + 112]
    pop qword [curr_proc + 104]
    pop qword [curr_proc + 96]
    pop qword [curr_proc + 88]
    pop qword [curr_proc + 80]
    pop qword [curr_proc + 56]
    pop qword [curr_proc + 48]
    pop qword [curr_proc + 40]
    pop qword [curr_proc + 72]
    pop qword [curr_proc + 64]
    mov [curr_proc + 156], ds
    mov [curr_proc + 164], es
    mov [curr_proc + 172], fs
    mov [curr_proc + 180], gs

    jmp load_proc
'''

def generate_irq_asm_file(file_out_name):
	opened_file = open(file_out_name, "w")

	# global isr_wrapper funcs
	for i in range(IRQ_VECTORS):
		opened_file.write("global isr_wrapper_" + str(i) + "\n")

	opened_file.write("\nglobal load_main_proc\n")
	opened_file.write("\nextern curr_proc")
	opened_file.write("\nextern IRQ_handler")
	opened_file.write("\nextern context_switch")
	opened_file.write("\nextern curr_proc")
	opened_file.write("\nextern next_proc")
	opened_file.write("\nextern main_proc_ptr\n")

	opened_file.write("\nsection .text\n")
	opened_file.write("\ncommon_irq_handler:\n" +
						"    push rsi\n" +
						"    push rax\n" +
						"    push rbx\n" +
						"    push rcx\n" +
						"    push r8\n" +
						"    push r9\n" +
						"    push r10\n" +
						"    push r11\n" +
						"    push r12\n" +
						"    push r13\n" +
						"    push r14\n" +
						"    push r15\n" +
						"    push rbp\n" +
						"    call IRQ_handler\n" +
						"    jmp check_for_context_switch\n\n")
	opened_file.write("\ncheck_for_context_switch:\n" +
						"    mov rsi, [curr_proc]\n" +
						"    mov rdx, [next_proc]\n" +
						"    cmp rsi, rdx\n" +
						"    je pop_the_stack\n"
						"    cmp rsi, 0\n" +
						"    je load_proc\n" +
						"    jmp save_proc\n\n")
	opened_file.write("pop_the_stack:\n" +
						"    pop rbp\n" +
						"    pop r15\n" +
						"    pop r14\n" +
						"    pop r13\n" +
						"    pop r12\n" +
						"    pop r11\n" +
						"    pop r10\n" +
						"    pop r9\n" +
						"    pop r8\n" +
						"    pop rcx\n" +
						"    pop rbx\n" +
						"    pop rax\n" +
						"    pop rsi\n" +
						"    pop rdi\n\n" +
						"    iretq\n\n")
	opened_file.write("\nload_proc:\n" +
						# replace iretq stack
						"    mov rsi, [next_proc] \n" +
						"    mov rdx, [rsi] \n" +
						"    mov [rsp + 112], rdx \n" +
						"    mov rdx, [rsi + 8] \n" +
						"    mov [rsp + 120], rdx \n" +
						"    mov rdx, [rsi + 16] \n" +
						"    mov [rsp + 128], rdx \n" +
						"    mov rdx, [rsi + 24] \n" +
						"    mov [rsp + 136], rdx \n" +
						"    mov rdx, [rsi + 32] \n" +
						"    mov [rsp + 144], rdx \n\n" +
						# replace regs on stack
						"    mov rdx, [rsi + 144]\n" +   #rbp
						"    mov [rsp], rdx\n" +
						"    mov rdx, [rsi + 136]\n" +   #r15
						"    mov [rsp + 8], rdx\n" +
						"    mov rdx, [rsi + 128]\n" +   #r14
						"    mov [rsp + 16], rdx\n" +
						"    mov rdx, [rsi + 120]\n" +   #r13
						"    mov [rsp + 24], rdx\n" +
						"    mov rdx, [rsi + 112]\n" +   #r12
						"    mov [rsp + 32], rdx\n" +
						"    mov rdx, [rsi + 104]\n" +   #r11
						"    mov [rsp + 40], rdx\n" +
						"    mov rdx, [rsi + 96]\n" +    #r10
						"    mov [rsp + 48], rdx\n" +
						"    mov rdx, [rsi + 88]\n" +    #r9
						"    mov [rsp + 56], rdx\n" +
						"    mov rdx, [rsi + 80]\n" +    #r8
						"    mov [rsp + 64], rdx\n" +
						"    mov rdx, [rsi + 56]\n" +    #rcx
						"    mov [rsp + 72], rdx\n" +
						"    mov rdx, [rsi + 48]\n" +    #rbx
						"    mov [rsp + 80], rdx\n" +
						"    mov rdx, [rsi + 40]\n" +    #rax
						"    mov [rsp + 88], rdx\n" +
						"    mov rdx, [rsi + 64]\n" +    #rdi
						"    mov [rsp + 104], rdx\n" +
						"    mov ds, [rsi + 156]\n" +    #seg regs
						"    mov es, [rsi + 164]\n" +
						"    mov fs, [rsi + 172]\n" +
						"    mov gs, [rsi + 180]\n" +
						#update curr_proc
						"    mov [curr_proc], rsi\n\n" +
						"    mov rdx, [rsi + 72]\n" +    #rsi
						"    mov [rsp + 96], rdx\n\n" +
						"    jmp pop_the_stack\n\n")
	opened_file.write("\nsave_proc:\n" +
						# save iretq stack
						"    mov rsi, [curr_proc] \n" +
						"    mov rdx, [rsp + 112] \n" +  #rip
						"    mov [rsi], rdx \n" +
						"    mov rdx, [rsp + 120] \n" +  #cs
						"    mov [rsi + 8], rdx \n" +
						"    mov rdx, [rsp + 128] \n" +  #rflags
						"    mov [rsi + 16], rdx \n" +
						"    mov rdx, [rsp + 136] \n" +  #rsp
						"    mov [rsi + 24], rdx \n" +
						"    mov rdx, [rsp + 144] \n" +  #ss
						"    mov [rsi + 32], rdx \n\n" +
						# save regs on stack
						"    mov rdx, [rsp]\n" +         #rbp
						"    mov [rsi + 144], rdx\n" +
						"    mov rdx, [rsp + 8]\n" +     #r15
						"    mov [rsi + 136], rdx\n" +
						"    mov rdx, [rsp + 16]\n" +    #r14
						"    mov [rsi + 128], rdx\n" +
						"    mov rdx, [rsp + 24]\n" +    #r13
						"    mov [rsi + 120], rdx\n" +
						"    mov rdx, [rsp + 32]\n" +    #r12
						"    mov [rsi + 112], rdx\n" +
						"    mov rdx, [rsp + 40]\n" +    #r11
						"    mov [rsi + 104], rdx\n" +
						"    mov rdx, [rsp + 48]\n" +    #r10
						"    mov [rsi + 96], rdx\n" +
						"    mov rdx, [rsp + 56]\n" +    #r9
						"    mov [rsi + 88], rdx\n" +
						"    mov rdx, [rsp + 64]\n" +    #r8
						"    mov [rsi + 80], rdx\n" +
						"    mov rdx, [rsp + 72]\n" +    #rcx
						"    mov [rsi + 56], rdx\n" +
						"    mov rdx, [rsp + 80]\n" +    #rbx
						"    mov [rsi + 48], rdx\n" +
						"    mov rdx, [rsp + 88]\n" +    #rax
						"    mov [rsi + 40], rdx\n" +
						"    mov rdx, [rsp + 104]\n" +   #rdi
						"    mov [rsi + 64], rdx\n" +
						"    mov [rsi + 156], ds\n" +    #ds
						"    mov [rsi + 164], es\n" +    #es
						"    mov [rsi + 172], fs \n" +   #fs
						"    mov [rsi + 180], gs \n\n" + #gs
						"    mov rdx, [rsp + 96]\n" +   #rsi
						"    mov [rsi + 72], rdx\n" +
						"    jmp load_proc\n\n")
	opened_file.write("\nload_main_proc:\n" +
						# Replace iretq stack
						"    mov rsi, [main_proc_ptr] \n" + #rip
						"    mov rdx, [rsi] \n" +
						"    mov [rsp + 112], rdx \n" +
						"    mov rdx, [rsi + 8] \n" +       #cs
						"    mov [rsp + 120], rdx \n" +
						"    mov rdx, [rsi + 16] \n" +      #rflags
						"    mov [rsp + 128], rdx \n" +
						"    mov rdx, [rsi + 24] \n" +      #rsp
						"    mov [rsp + 136], rdx \n" +
						"    mov rdx, [rsi + 32] \n" +      #ss
						"    mov [rsp + 144], rdx \n\n" +
						# Replace registers on stack
						"    mov rdx, [rsi + 144]\n" +   #rbp
						"    mov [rsp], rdx\n" +
						"    mov rdx, [rsi + 136]\n" +   #r15
						"    mov [rsp + 8], rdx\n" +
						"    mov rdx, [rsi + 128]\n" +   #r14
						"    mov [rsp + 16], rdx\n" +
						"    mov rdx, [rsi + 120]\n" +   #r13
						"    mov [rsp + 24], rdx\n" +
						"    mov rdx, [rsi + 112]\n" +   #r12
						"    mov [rsp + 32], rdx\n" +
						"    mov rdx, [rsi + 104]\n" +   #r11
						"    mov [rsp + 40], rdx\n" +
						"    mov rdx, [rsi + 96]\n" +    #r10
						"    mov [rsp + 48], rdx\n" +
						"    mov rdx, [rsi + 88]\n" +    #r9
						"    mov [rsp + 56], rdx\n" +
						"    mov rdx, [rsi + 80]\n" +    #r8
						"    mov [rsp + 64], rdx\n" +
						"    mov rdx, [rsi + 56]\n" +    #rcx
						"    mov [rsp + 72], rdx\n" +
						"    mov rdx, [rsi + 48]\n" +    #rbx
						"    mov [rsp + 80], rdx\n" +
						"    mov rdx, [rsi + 40]\n" +    #rax
						"    mov [rsp + 88], rdx\n" +
						"    mov rdx, [rsi + 64]\n" +    #rdi
						"    mov [rsp + 104], rdx\n" +
						"    mov ds, [rsi + 156]\n" +    #seg regs
						"    mov es, [rsi + 164]\n" +
						"    mov fs, [rsi + 172]\n" +
						"    mov gs, [rsi + 180]\n" +
						"    mov rdx, [rsi + 72]\n" +    #rsi
						"    mov [rsp + 96], rdx\n\n" +
						#zero out proc ptrs
						"    mov qword [next_proc], 0\n" +
						"    mov qword [curr_proc], 0\n\n" +
						"    jmp pop_the_stack\n\n")

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
			   	  			  "    add rsp, 8\n" +
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
