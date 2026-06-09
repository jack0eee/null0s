#include "io.h"

/*
.------------------------------------------------.
| funzione outb necessaria per scrivere driver.  |
'------------------------------------------------' */
void outb(unsigned short int port, unsigned char value)
{
    __asm__ volatile (
       "outb %0,%1"
       :
       :"a"(value),"Nd"(port)
    );
}

/*
.------------------------------------------------.
| funzione outb necessaria per scrivere driver.  |
'------------------------------------------------' */
unsigned char inb(unsigned short int port)
{
    unsigned char ret;

    __asm__ volatile (
       "inb %1,%0"
       : "=a"(ret)
       : "Nd"(port)
    );

    return ret;
}

