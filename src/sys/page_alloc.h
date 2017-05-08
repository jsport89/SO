#ifndef PAGE_ALLOC_H
#define PAGE_ALLOC_H

#include <stdint-gcc.h>

#define FREE_POOL_SIZE 256
#define FIRST_AVAILABLE_ADDRESS 4000
#define PAGE_FRAME_SIZE 4000
#define MMP_ENTRY_SIZE 24
#define SH_ENTRY_SIZE 64


/* typdefs */
typedef struct {
  uint32_t tag_size;
  uint32_t reserved;
}__attribute__((packed)) Fixed_Header;

typedef struct {
  uint32_t tag_type;
  uint32_t tag_size;
}__attribute__((packed)) Generic_Tag;

typedef struct {
  uint32_t tag_type;
  uint32_t tag_size;
  uint32_t memory_info_entry_size;
  uint32_t memory_info_entry_version;
  /* Array of memory info entries. determined by (tag_size - 16bytes)*/
}__attribute__((packed)) Memory_Map_Tag;

typedef struct {
  uint64_t starting_address;
  uint64_t length;                           /* in bytes */
  uint32_t type;
  uint32_t reserved;
}__attribute__((packed)) Memory_Info_Entry;

/* Tag type 9 */
typedef struct {
  uint32_t tag_type;
  uint32_t tag_size;
  uint32_t number_of_section_header_entries;
  uint32_t section_header_entry_size;
  uint32_t index_of_section_with_string_table;
  /* section header array */
}__attribute__((packed)) ELF_Section_Header;

typedef struct {
  uint32_t section_name;                      /* as an index into the string table */
  uint32_t section_type;                      /* type of section */
  uint64_t flags;
  uint64_t segment_address;                   /* address of segment in memory */
  uint64_t segment_offset;                    /* offset of segment in file on disk */
  uint64_t segment_size;                      /* bytes */
  uint32_t table_index_link;
  uint32_t extra_info;
  uint32_t address_alignment;                 /* powers of 2 */
  uint64_t fixed_entry_size;                  /* IFF section holds fixed entries */
}__attribute__((packed)) Section_Header_Entry;

typedef struct {
   uint64_t size;
   uint64_t last_free_page;
}__attribute__((packed)) Free_Pool;

typedef struct {
   uint64_t first_mmp_low_limit;
   uint64_t first_mmp_high_limit;
   uint64_t second_mmp_low_limit;
   uint64_t second_mmp_high_limit;
   uint64_t next_available_address;
}__attribute__((packed)) Available_Pages;

/* Functions */

#endif /* page_alloc.h */
