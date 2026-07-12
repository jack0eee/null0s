
/* string.h di libc stardard [valido per C89/C90/C99] */

#ifndef STRING_H
#define STRING_H

#include "stddef.h" //?????????????????
#include "stdint.h" //????????????????? 

/* --- gestione delle stringhe [7] --- */

size_t strlen  (const char *s);                              
int    strcmp  (const char *s1, const char *s2);              
int    strncmp (const char *s1, const char *s2, size_t n);
char  *strcpy  (char *restrict dest, const char *restrict src);
char  *strncpy (char *restrict dest, const char *restrict src, size_t n);
char  *strcat  (char *restrict dest, const char *restrict src);
char  *strncat (char *restrict dest, const char *restrict src, size_t n);


/* --- ricerca e scansione [4/6] --- */ 

char  *strchr  (const char *s, int c);                         
char  *strrchr (const char *s, int c);                             
char  *strstr  (const char *haystack, const char *needle);         
char  *strpbrk (const char *s, const char *accept);                
size_t strspn  (const char *s, const char *accept);  
size_t strcspn (const char *s, const char *reject);  


/* --- tokenizzazione [0/1] --- */ 

char  *strtok (char *s, const char *delim);                       // NO 1 


/* --- gestione errori [0/1] --- */

char  *strerror (int errnum);                                     // NO 2 


/* --- funzioni su memoria grezza / ignorano il terminatore [5] --- */

void  *memcpy  (void *dest     , const void *src , size_t n); 
void  *memset  (void *s        , int c           , size_t n);
void  *memmove (void *dest     , const void *src , size_t n);     
int    memcmp  (const void *s1 , const void *s2  , size_t n);
void  *memchr  (const void *s  , int c           , size_t n);

// ------ in elenco : 20 -- implementate : 18 -- da implementare : 2  
 
#endif 

/* EOF */

