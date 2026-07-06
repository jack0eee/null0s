
/* 
    --- stddef di libc stardard | specializzata architettura CPU i86 16bit) ---
          CPU: 80386, 80486, PentiumI, PentiumPro, PentiumII, PentiumIII
*/

#ifndef STDDEF_H
#define STDDEF_H

/* 
.----------------.
| ssize_t|size_t '----------------------------------------.
| Grande da contenere la dimensione massima indirizzabile |
| sizeof(int)=4 Quindi XXXXXXX (size_t)                   | 
'---------------------------------------------------------' */
typedef signed   int      ssize_t;
typedef unsigned int       size_t;

/*
.--------------------.
| intptr_t|uintptr_t '-------------------------------------------------.
| Grande da contenere un indirizzo di memoria convertiti ad un intero. |
'----------------------------------------------------------------------' */
typedef signed   int     intptr_t;
typedef unsigned int    uintptr_t;

#endif

/* EOF */
