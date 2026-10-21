
/* stdint di libc stardard | Comuni a tutte le architetture */

#ifndef STDINT_H
#define STDINT_H

/*
.---------------------.
| int8_t ed uiunt8_t  '-----------------------------------------. 
| Universalmente a 8bit su tutte le architetture (8,16,32 e 64) |
'---------------------------------------------------------------' */
typedef signed   char    int8_t  ;
typedef unsigned char   uint8_t  ;

/*
.-----------------------.
| int16_t ed uiunt16_t  '----------------------------------------.
| Universalmente a 16bit su tutte le architetture (8,16,32 e 64) |
'----------------------------------------------------------------' */
typedef signed   short   int16_t ;
typedef unsigned short  uint16_t ;

/*
.-----------------------.
| int32_t ed uiunt32_t  '---------------------------------------.
| Valide per architetture i386 e x86_64 (32 e 64 bit)           |
'---------------------------------------------------------------' */
typedef signed   long    int32_t ;
typedef unsigned long   uint32_t ;

/*
.-----------------------.
| int64_t ed uiunt64_t  '---------------------------------------.
| Valide per architetture i386 e x86_64 (32 e 64 bit)           |
'---------------------------------------------------------------' */
typedef signed   long long   int64_t ;
typedef unsigned long long  uint64_t ;

//========================== M A C R O ==========================

/*
.-------.
| NULL  '-------------------------------------------------------.
| E' una macro che rappresenta un puntatore invalido/non        |
| associato a nessuna stringa. Una convenzione utile.           |
| Lo standard non specifica come definirlo, in alcuni casi      |
| semplicemente sostituito con uno 0 (zero).                    |
| Preferisco in quetso caso seguir ela definizione storica,     |
| utilizzata anche da gnu glibc.                                |
'---------------------------------------------------------------' */
#define NULL ((void *)0)


#endif

/* EOF */
