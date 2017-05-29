/*
 * malloc.c - contains implementations of memory manipulation
 * functions.
 * TODO:
 * + implement brk() - grow heap by specified amount
 * + and brk() - that sets top of heap to given address
 */
#include "so_kmalloc.h"
#include "so_string.h"
#include "so_stdio.h"
#include "types.h"
#include "../drivers/interrupts.h"
#include "../sys/virtual_page_alloc.h"
#include "../sys/mmu.h"

#define ALIGN_DIV_NUM 8
#define alignBy(x) ((((x)/ALIGN_DIV_NUM)+1)*ALIGN_DIV_NUM)
#define divBy(x) ((x)%ALIGN_DIV_NUM)
#define SMALLEST_CHUNK 16
#define CHUNK_INFO_SIZE 32
#define VALID 1
#define INVALID 0
#define HEAP_INIT 6400


/* Globals */
static void *start_of_heap = NULL;
//static void *end_of_heap = NULL;  NOT IN USE YET
extern uint64_t next_virtual_address;
static uint64_t brk_point = KHEAP_START;
static uint64_t brk_point_in_pages = KHEAP_START;

/* Prototypes */
void *kmalloc(size_t size);
void kfree(void *ptr);
void *kcalloc(size_t nmemb, size_t size);
void kmalloc_lib_test(void);


/* helpers */
static Chunk_Info *find_free_chunk(Chunk_Info **last_chunk, size_t size);
static size_t calc_size(size_t size);
static void split_chunk(Chunk_Info *cur_chunk, size_t size);
static Chunk_Info *grow_heap(Chunk_Info *last_chunk, size_t size);
static int validate_address(void *to_check);
static Chunk_Info *get_chunk_start(void *cur_chunk_data);
static Chunk_Info *fuse_chunks(Chunk_Info *cur_chunk);

//static int brk(void *addr);
void *brk(uintptr_t incr);

/*
-Create a kernel brk (top of heap) pointer similar in intent to a process’s brk.
-This is literally just a pointer to the next unused page in the heap area of the
virtual address space.
– When more heap space is needed use the virtual page allocator to create space
(rounded up to a page size) at the brk address.
– Increment brk by the amount allocated.
*/
/*
 * Lock this for race conditions
 * Increment brk_point by incr.
 * IF brk_point > brk_point_in_pages
 *    MMU_alloc | brk_point < brk_point_in_pages
 */
void *brk(uintptr_t incr) {
   uint64_t to_return = brk_point;
   brk_point += incr;

   if (to_return > USERSPACE_START) {
      return (void *)-1;
   }

   if (0 == incr) {
      return (void *)to_return;
   }

   if (brk_point > brk_point_in_pages) {
      while (brk_point > brk_point_in_pages) {
         MMU_alloc_page();
         brk_point_in_pages += PAGE_FRAME_SIZE;
      }
   }

   return (void *)to_return;
}

/* Implementations */


/*
 * IF start_of_heap IS NULL
 *    Align the beginning
 *    Grow heap by HEAP_INIT
 *    Set cur_chunk to a big ole hunk of memory
 * IF start_of_heap exists
 *    find a free chunk for size
 *    IF free chunk exists
 *       possibly split
 *    ELSE
 *       grow the heap
 */
void *kmalloc(size_t size) {
   void *set_heap_start;
   size_t offset;
   Chunk_Info *last_chunk, *cur_chunk;

   size_t chunk_size = calc_size(size);

   if (!start_of_heap) {
      set_heap_start = brk(0);
      offset = ALIGN_DIV_NUM - (int)((uintptr_t)set_heap_start % ALIGN_DIV_NUM);

      if (offset < ALIGN_DIV_NUM)
         set_heap_start = brk(offset);
      set_heap_start = brk(0);
      offset = (int)((uintptr_t)set_heap_start % ALIGN_DIV_NUM);

      cur_chunk = grow_heap(NULL, HEAP_INIT);


// ADDED, POTENTIALLY REMOVE
      cur_chunk->available = AVAIL;


      if (!cur_chunk) {
         // errno = ENOMEM;
         return NULL;
      }
      start_of_heap = cur_chunk;
   }

   if (start_of_heap) {
      last_chunk = start_of_heap;
      cur_chunk = find_free_chunk(&last_chunk, chunk_size);

      if (cur_chunk) {
         if ((cur_chunk->size - chunk_size) >= (CHUNK_INFO_SIZE + SMALLEST_CHUNK)) {
            split_chunk(cur_chunk, chunk_size);
         }

      }
      else {
         cur_chunk = grow_heap(last_chunk, chunk_size);
         if(!cur_chunk) {
            // errno = ENOMEM;
            return NULL;
         }
      }
   }
   cur_chunk->available = NOT_AVAIL;
// Debugging
/*
   printk("Malloc'd block:\n");
   printk("size: %u.\n", cur_chunk->size);
   printk("next: %p.\n", cur_chunk->next);
   printk("prev: %p.\n", cur_chunk->prev);
   printk("avail: %u.\n\n", cur_chunk->available);
*/
   return (void *)((uintptr_t)cur_chunk + CHUNK_INFO_SIZE);
}

void *kcalloc(size_t nmemb, size_t size) {
   void *new_chunk;
   size_t chunk_size = calc_size(nmemb * size);

   new_chunk = kmalloc(chunk_size);
   memset(new_chunk, 0, chunk_size);

   return new_chunk;
}

/*
 * Check if address being free'd is legit
 * Get start of ptr (meta of ptr)
 * Attempt to fuse previous with ptr
 * IF next chunk is free, fuse_chunks
 * ELSE
 *    IF cur_chunk->prev exists
 *       set cur_chunk->prev->next to NULL
 *    ELSE (we're at the one and only chunk in the heap)
 *       start_of_heap = NULL
 *    Set break value to beginning of free'd chunk.
 */
void kfree(void *ptr) {
   Chunk_Info *cur_chunk;

   if (!validate_address(ptr)) {
      printk("KMALLOC: Invalid malloc address attempted to be free'd.\n");
      for(;;) {
        __asm__("hlt");
      }
      return;
   }

   cur_chunk = get_chunk_start(ptr);
   cur_chunk->available = AVAIL;

/* DEBUGGING  */
   printk("Block to free:\n");
   printk("block free'd address: %p.\n", cur_chunk);
   printk("size: %u.\n", cur_chunk->size);
   printk("next: %p.\n", cur_chunk->next);
   printk("prev: %p.\n", cur_chunk->prev);
   printk("avail: %u.\n\n", cur_chunk->available);

   if (cur_chunk->prev && cur_chunk->prev->available)
      cur_chunk = fuse_chunks(cur_chunk->prev);

   if (cur_chunk->next)
      fuse_chunks(cur_chunk);
   else {
      if (cur_chunk->prev) {
         cur_chunk->prev->next = NULL;
         //brk(cur_chunk);                             // Implement this
      }
      else {
         start_of_heap = NULL;// RESET BRK (not page size) *****
         brk_point = KHEAP_START;
         //brk(KHEAP_START);                           // Implement this. Set it to NULL
      }
   }
}

/* Traverse list of available mem chunks */
static Chunk_Info *find_free_chunk(Chunk_Info **last_chunk, size_t size) {
   Chunk_Info *cur_chunk = start_of_heap;

   while(cur_chunk && !(cur_chunk->available && cur_chunk->size >= size)) {
      *last_chunk = cur_chunk;
      cur_chunk = (void *)cur_chunk->next;
   }

   return cur_chunk;
}

/* Grow heap given a size */
static Chunk_Info *grow_heap(Chunk_Info *last_chunk, size_t size) {
   Chunk_Info *cur_chunk;

   cur_chunk = brk(0);

   if (brk(CHUNK_INFO_SIZE + size) == (void*)-1) {
      // errno = ENOMEM
      return NULL;
   }

   cur_chunk->size = size;
   cur_chunk->next = NULL;
   cur_chunk->prev = last_chunk;

   if (last_chunk) {
      last_chunk->next = (void *)cur_chunk;
      cur_chunk->available = NOT_AVAIL;
   }

   return cur_chunk;
}

/*
 * Carve a 'new_chunk' off of cur_chunk.
 * [cur_chunk] --> [cur_chunk][new_chunk]
 */
static void split_chunk(Chunk_Info *cur_chunk, size_t size) {
   Chunk_Info *new_chunk;

   new_chunk = (void *)((uintptr_t)cur_chunk + CHUNK_INFO_SIZE + size);
   new_chunk->size = cur_chunk->size - CHUNK_INFO_SIZE - size;
   new_chunk->next = cur_chunk->next;

   if (cur_chunk->next)
      new_chunk->next->prev = new_chunk;

   new_chunk->prev = cur_chunk;
   new_chunk->available = AVAIL;
   cur_chunk->size = size;
   cur_chunk->next = (void *)new_chunk;
   cur_chunk->available = NOT_AVAIL;
}

static size_t calc_size(size_t size) {
   size_t right_size = divBy(size) ? alignBy(size) : size;
   return right_size;
}


static Chunk_Info *fuse_chunks(Chunk_Info *cur_chunk) {
   if (cur_chunk->next && cur_chunk->next->available) {
      cur_chunk->size = CHUNK_INFO_SIZE + cur_chunk->size + cur_chunk->next->size;

      cur_chunk->next = cur_chunk->next->next;

      if (cur_chunk->next)
         cur_chunk->next->prev = cur_chunk;
   }
   return cur_chunk;
}

static Chunk_Info *get_chunk_start(void *cur_chunk_data) {
   cur_chunk_data = (void *)((uintptr_t)cur_chunk_data - CHUNK_INFO_SIZE);
   return cur_chunk_data;
}

static int validate_address(void *to_check) {
   Chunk_Info *cur_chunk = start_of_heap;

   if (start_of_heap) {
      while (cur_chunk != NULL) {
         if (cur_chunk->available == NOT_AVAIL &&
            to_check == (void *)((uintptr_t)cur_chunk + CHUNK_INFO_SIZE))
            return VALID;
         cur_chunk = cur_chunk->next;
      }
   }
   return INVALID;
}

/*
 * check the field for trap or fault in
 */

void kmalloc_lib_test() {
   uint64_t size = 1000;

// Reuse chunk
   char *some_char = (char *)kmalloc(size);
   printk("1 malloc address: %p.\n", some_char);

   kfree(some_char);

   some_char = kmalloc(size);
   printk("2 malloc address: %p.\n", some_char);

   some_char = kmalloc(size);
   printk("3 malloc address: %p.\n", some_char);

   kfree(some_char);

   some_char = kmalloc(size);
   printk("4 malloc address: %p.\n", some_char);


// Alloc and free
/* Debugging */
   int i = 1;
   while(i);

   uint64_t to_alloc = 10000;
   void *allocd_ptrs[to_alloc];
   for (int i = 0; i < to_alloc; i++) {
/* BUG HERE, size => ~809384903842 */
      allocd_ptrs[i] = kmalloc(size);
      printk("kmallocd %d.\n", i);
   }

   for (int i = 0; i < to_alloc; i++) {
      kfree(allocd_ptrs[i]);
      printk("kfree %d.\n", i);
   }




// Exhaust memory
/*
   void *to_print;
   while(1) {
      to_print = kmalloc(1000000);
      printk("malloc'd: %p\n", to_print);
   }
*/

}

/*
Get GPF stack address
Trigger gpf.
Analyze GPF stack address to get rip.
 */
