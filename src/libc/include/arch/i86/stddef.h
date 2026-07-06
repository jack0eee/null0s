
/* 
    --- stddef di libc stardard | specializzata architettura CPU i86 16bit) ---
                        CPU: 8086, 8088, 80186, 80286
*/

#ifndef STDDEF_H
#define STDDEF_H

/* 
.----------------.
| ssize_t|size_t '----------------------------------------.
| Grande da contenere la dimensione massima indirizzabile |
| sizeof(short)=2 Quindi 65535 (size_t) 
'---------------------------------------------------------' */
typedef signed   short    ssize_t;
typedef unsigned short     size_t;

/*
.--------------------.
| intptr_t|uintptr_t '-------------------------------------------------.
| Grande da contenere un indirizzo di memoria convertiti ad un intero. |
'----------------------------------------------------------------------' */
typedef signed   short   intptr_t;
typedef unsigned short  uintptr_t;

#endif

/* EOF */
