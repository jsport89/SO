/*
 * proc.h
 * TODO:
 * - enable disable interrupts in functions
 */
#include "proc.h"
#include "so_kmalloc.h"
#include "so_stdlib.h"
#include "so_stdio.h"
#include "types.h"
#include "../drivers/interrupts.h"

#define STACK_SIZE 2048

/* Globals */
Process *main_proc_ptr = NULL;
static uint64_t pids = 0;
Process main_proc;
Process *curr_proc = NULL;
Process *next_proc = NULL;


/* Scheduler data */
Process *scheduler_head = NULL;

/* Prototypes */
void init_proc(void);
void PROC_run(void);
Process *PROC_create_kthread(kproc_t entry_point, void *arg);
void PROC_reschedule(void);
void yield(void);
void kexit(void);
void exit_handler(int unused, int unused_2, int unused_3, int unused_4, int syscall_num);
void yield_handler(int unused, int unused_2, int unused_3, int unused_4, int syscall_num);


void PROC_block_on(ProcessQueue *queue, int enable_ints);
void PROC_unblock_all(ProcessQueue *queue);
void PROC_unblock_head(ProcessQueue *queue);
void PROC_init_queue(ProcessQueue *queue);
void unlink_proc(Process *curr_proc, ProcessQueue *proc_queue);
void append_proc(Process *curr_proc, ProcessQueue *queue);


/* SYSCALL stuff */
void common_syscall(int unused, int unused_2, int unused_3, int unused_4, int syscall_num);
void exit_syscall(int unused, int unused_2, int unused_3, int unused_4, int syscall_num);
void common_syscall_handler(int unused, int unused_2, void *arg);
void load_main_proc(void);
void save_main_proc(void);


/* Scheduler Prototypes */
void rr_admit(Process *new);
void rr_remove(Process *victim);
Process *rr_next(void);


/* Scheduler functions */
void rr_admit(Process *new_proc) {
   Process *current = scheduler_head;

   if(!scheduler_head) {
      scheduler_head = new_proc;
      //curr_proc = scheduler_head;
   }
   else {
      while(current->next != NULL) {
         current = current->next;
      }

      current->next = new_proc;
   }

   new_proc->next= NULL;
}

void rr_remove(Process *victim) {
   Process *current = scheduler_head;

/* Cases:
 * - Empty list
 * - One item
 * - Multiple items
 */
   if(!scheduler_head)
      return;

   if(victim == current && current->next == NULL) {
      scheduler_head = NULL;
      curr_proc = scheduler_head;
      //next_proc = main_proc_ptr;
      return;
   }

   while(current->next != NULL) {
      if(victim == scheduler_head) {
         scheduler_head = scheduler_head->next;
         return;
      }

      if(victim == current->next) {
         current->next = current->next->next;
         return;
      }

      current = current->next;
   }
}


/* Functions */
void init_proc() {
   /* CLI */
   int enable_ints = INTS_OFF;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   IRQ_set_handler(SYSCALL_IRQ_NUM, common_syscall_handler, NULL); // For syscalls
   syscall_set_handler(YIELD_SYSCALL_NUM, yield_handler);

   IRQ_set_handler(EXIT_SYSCALL_IRQ_NUM, common_syscall_handler, NULL);
   syscall_set_handler(EXIT_SYSCALL_NUM, exit_handler);

// SET EXIT SYSCALL STACK SOMEWHERE HERE
   Global_IDT[EXIT_SYSCALL_IRQ_NUM].isti = 5;

   // SYSCALL_set_handler(); for yield AND exit
   // Global_IDT[EXIT_SYSCALL_NUM]. = ;

   /* STI */
   if (enable_ints) {
      STI
   }
}

void yield() {
   common_syscall(0, 0, 0, 0, YIELD_SYSCALL_NUM);
}

void kexit() {
   // Trigger trap to destroy process
   exit_syscall(0, 0, 0, 0, EXIT_SYSCALL_NUM);
}

// If no processes in scheduler exist, return.
void PROC_run() {
   int enable_ints = INTS_OFF;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   main_proc_ptr = &main_proc;
   main_proc_ptr->next = scheduler_head;
   main_proc_ptr->stack = NULL;
   main_proc_ptr->cs = 0x8;
   curr_proc = &main_proc;
   // next_proc = scheduler_head;
   yield();

   if (enable_ints) {
      STI
   }
}

Process *PROC_create_kthread(kproc_t entry_point, void *arg) {
   uint64_t *stack_pointer = NULL;
   int enable_ints = INTS_OFF;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   Process *new_proc = kcalloc(1, sizeof(Process));
   if (!new_proc) {
      printk("PROC: Bad kmalloc on process.\n");
      for(;;) {
        __asm__("hlt");
      }
   }

   new_proc->stack = kcalloc(STACK_SIZE, sizeof(uint64_t));
   if (!new_proc->stack) {
      printk("PROC: Bad kmalloc on process stack.\n");
      for(;;) {
        __asm__("hlt");
      }
   }

   // Setup stack
   stack_pointer = new_proc->stack + STACK_SIZE;
   stack_pointer--;
   stack_pointer--;
   *stack_pointer = (uint64_t)kexit;
   stack_pointer--;

   // Init registers
   new_proc->pid = pids;
   pids++;
   new_proc->rdi = (uint64_t)arg;
   new_proc->rbp = (uint64_t)stack_pointer;
   new_proc->rip = (uint64_t)entry_point;
   new_proc->rsp = (uint64_t)stack_pointer;
   new_proc->cs = 0x8;     // Kernel code segment address
   new_proc->ss = 0;       // Stack selector
   new_proc->rflags = 512; // Set interrupt flag
   new_proc->next = NULL;

   // Admit process into scheduler
   rr_admit(new_proc);

   if (enable_ints) {
      STI
   }

   return new_proc;
}

// Selects next thread to run
void PROC_reschedule(void) {
   int enable_ints = INTS_OFF;

   if (are_interrupts_enabled()) {
      enable_ints = INTS_ON;
      CLI
   }

   next_proc = curr_proc->next;

   // Are we at the end of the LL?
   if (!next_proc)
      next_proc = scheduler_head;

   if (!next_proc) {
      next_proc = main_proc_ptr;
      if (enable_ints) {
         STI
      }
      return;
   }

   // Calling proc is the ONLY proc.
   if (next_proc == curr_proc) {
      if (enable_ints) {
         STI
      }
      return;
   }

   if (enable_ints) {
      STI
   }
   //next_proc = curr_proc->next;
}
/*
 * syscall - initiates syscall interrupt with syscall_num to fetch
 */
void common_syscall(int unused, int unused_2, int unused_3, int unused_4, int syscall_num) {
   //asm volatile("INT $123");
   asm("int $123");
}

/*
 * syscall - initiates exit_syscall interrupt with syscall_num to fetch
 */
void exit_syscall(int unused, int unused_2, int unused_3, int unused_4, int syscall_num) {
   asm("int $128");
}

/*
 * Generic common syscall handler
 * Get syscall # from reg
 * Bounds check syscall number
 * Index into syscall table
 * Call associated c function
 */
void common_syscall_handler(int unused, int unused_2, void *arg) {
   uint64_t syscall_index;
   __asm__("movq %%r8, %0" : "=r"(syscall_index));

   if (syscall_index <= SCT_SIZE && syscall_index >= 0) {
      execute_syscall(syscall_index);
   }
}


/*
Formerly, yield_syscall_handler
Invoke scheduler to pass control to next thread
- Return if i cur_proc == next_proc
Save cur_proc context
Load next_proc context
 */
void yield_handler(int unused, int unused_2, int unused_3, int unused_4, int syscall_num) {
   // Update next_proc
   PROC_reschedule();
}

/*
Get beginning of stack (to free)
Remove proc from scheduler
Advance scheduler to next_proc
Free cur_proc
Free cur_proc stack
IF nothing in scheduler, load main_proc
ELSE load next_proc
 */
void exit_handler(int unused, int unused_2, int unused_3, int unused_4, int syscall_num) {
// Remove thread from handler
// Reschedule
// Free stack
// Free process struct
// ZERO OUT CURR_PROC

   Process *to_free = curr_proc;

   rr_remove(to_free);

   PROC_reschedule();                /* Updating curr_proc where? */
   curr_proc = 0;                    // ZERO this

   kfree(to_free->stack);
   kfree(to_free);

/* Possibly load main proc state here if both cur proc and next proc == NULL*/
   if (!scheduler_head && !curr_proc) {
      next_proc = main_proc_ptr;
      load_main_proc();
   }
}

/*
 Blocks a
 process, however make special note of the race condition
 */
void PROC_block_on(ProcessQueue *queue, int enable_ints) {

}

/*
Unblocks all processes from
the ProcessQueue, moving them all back to the scheduler.
 */
void PROC_unblock_all(ProcessQueue *queue) {

}

/*
Unblocks one process
from the ProcessQueue, moving it back to the scheduler.
 */
void PROC_unblock_head(ProcessQueue *queue) {

}

/*
Initializes a ProcessQueue
structure (mainly sets head to NULL).
Called once for each ProcessQueue during
driver initialization.
 */
void PROC_init_queue(ProcessQueue *queue) {

}

void unlink_proc(Process *curr_proc, ProcessQueue *proc_queue) {

}

void append_proc(Process *curr_proc, ProcessQueue *queue) {

}
