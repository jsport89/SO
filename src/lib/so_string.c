/* so_string.c - Implementations of functions from so_string.h */
/*
 * TODO: Implement strdup.
 */
#include "so_string.h"

void *memset(void *dst, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
int strcmp(const char *s1, const char *s2);
const char *strchr(const char *s, int c);
char *strdup(const char *s);

/* Initializes dst to (dst + n) with init_val */
void *memset(void *dst, int init_val, size_t n) {
   unsigned char *uchar_dst = dst;

   for (int i = 0; i < n; i++)
      *(uchar_dst + i) = (unsigned char)init_val;

   return dst;
}

/* Copies n chars from src to dest */
void *memcpy(void *dest, const void *src, size_t n) {
   char *char_dest;
   const char *char_src;
   char_dest = dest;
   char_src = src;

   for (int i = 0; i < n; i++)
      *(char_dest + i) = *(char_src + i);

   return dest;
}

/* returns length of a given array of chars*/
size_t strlen(const char *s) {
   size_t len = 0;

   while ('\0' != *s) {
      len++;
      s++;
   }

   return len;
}

/* Copies string from src to dest */
char *strcpy(char *dest, const char *src) {
   int i = 0;

   while ('\0' != *(src + i)) {
      *(dest + i) = *(src + i);
      i++;
   }

   /* NULL term dest */
   *(dest + i) = '\0';

   return dest;
}

/* compares s1 to s2 */
int strcmp(const char *s1, const char *s2) {

   while (*s1 && (*s1 == *s2)) {
      s1++;
      s2++;
   }
   return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

/* Locates first occurrence of c in s  */
const char *strchr(const char *s, int c) {
   while (*s != (char)c) {
      if ('\0' == (*s++))
         return NULL;
   }
   return (char *)s;
}

/* returns a pointer to a new string which is duplicate of s  */
/*
char *strdup(const char *s) {
   char *copy;
   size_t s_size;

   s_size = strlen(s) + 1;

   if (NULL == (copy = malloc(sizeof(char) * s_size)))
      return NULL;

   (void)memcpy(copy, s, s_size);

   return copy;
}
*/
