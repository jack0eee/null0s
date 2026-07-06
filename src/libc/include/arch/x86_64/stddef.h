
/* 
    --- stddef di libc stardard | specializzata architettura CPU i86 16bit) ---
                             CPU: amd64, x86_64
*/

#ifndef STDDEF_H
#define STDDEF_H

/* 
.----------------.
| ssize_t|size_t '----------------------------------------.
| Grande da contenere la dimensione massima indirizzabile |
| sizeof(long)=4 Quindi XXXXXX (size_t)                   | 
'---------------------------------------------------------' */
typedef signed   long     ssize_t;
typedef unsigned long      size_t;

/*
.--------------------.
| intptr_t|uintptr_t '-------------------------------------------------.
| Grande da contenere un indirizzo di memoria convertiti ad un intero. |
'----------------------------------------------------------------------' */
typedef signed   long    intptr_t;
typedef unsigned long   uintptr_t;

#endif

/* EOF */
