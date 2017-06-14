#ifndef PROC_H
#define PROC_H
#include <stdint-gcc.h>
#include "types.h"
#include "../drivers/interrupts.h"
#define SYSCALL_IRQ_NUM 123
#define EXIT_SYSCALL_IRQ_NUM 128
#define YIELD_SYSCALL_NUM 0
#define EXIT_SYSCALL_NUM 1

typedef void (*kproc_t)(void*);
/*
rax, rbx, rcx, rdx, rdi, rsi, r8, r9, r10, r11, r12, r13, r14, r15,
rbp, rsp, rip, rflags, cs, ss, ds, es, fs, gs
 */
typedef struct Process {
   /* iret frame */
   uint64_t rip;
   uint64_t cs;
   uint64_t rflags;
   uint64_t rsp;
   uint64_t ss;

   /* Other registers */
   uint64_t rax;   /* Registers */
   uint64_t rbx;
   uint64_t rcx;
   uint64_t rdi;
   uint64_t rsi;
   uint64_t r8;
   uint64_t r9;
   uint64_t r10;
   uint64_t r11;
   uint64_t r12;
   uint64_t r13;
   uint64_t r14;
   uint64_t r15;
   uint64_t rbp;
   uint64_t ds;
   uint64_t es;
   uint64_t fs;
   uint64_t gs;;

   // Page Table
   // File Descriptors
   uint64_t *stack;
   uint64_t pid;   /* Process ID */
   struct Process *next;
}__attribute__((packed)) Process;

typedef struct ProcessQueue {
   Process *head;

} __attribute__((packed)) ProcessQueue;

// Create stack struct to save registers

/* Globals */
extern Process *curr_proc;
extern Process *next_proc;
extern Process *main_proc_ptr;
extern Process *scheduler_head;

/* SYSCALL STUFF TO MOVE */
extern void load_main_proc(void);
extern void save_main_proc(void);

/* Functions */
void PROC_run(void);
Process *PROC_create_kthread(kproc_t entry_point, void *arg);
void PROC_reschedule(void);
void yield(void);
void kexit(void);
void init_proc(void);

void PROC_block_on(ProcessQueue *queue, int enable_ints);
void PROC_unblock_all(ProcessQueue *queue);
void PROC_unblock_head(ProcessQueue *queue);
void PROC_init_queue(ProcessQueue *queue);
void unlink_proc(Process *curr_proc, ProcessQueue *proc_queue);
void append_proc(Process *curr_proc, ProcessQueue *queue);

#endif /* proc.h */
