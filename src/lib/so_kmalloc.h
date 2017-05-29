#ifndef SO_MALLOC_H
#define SO_MALLOC_H

#include <stdint-gcc.h>
#include "types.h"


#define AVAIL 1
#define NOT_AVAIL 0

typedef struct Chunk_Info {
   uint64_t size;            // 8
   struct Chunk_Info *next;  // 8
   struct Chunk_Info *prev;  // 8
   uint32_t available;       // 4
} Chunk_Info;                // 28 bytes??

void *kmalloc(size_t size);
void kfree(void *ptr);
void *kcalloc(size_t nmemb, size_t size);

void kmalloc_lib_test();

#endif /* so_malloc.h */
