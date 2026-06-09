
/* stdio.h di libc stardard -- C ANSI  */

#ifndef STDIO_H
#define STDIO_H

#include "libvga.h" 

/*
.--------------------------------------------------.
| putchar | funzione che stampa un carattere       |
| in output. Prende come parametro il              |
| carattere da stampare e restituisce l'esito      |
| dell'operazione. Al momento al suo interno       |
| scrive direttamente nella memoria video VGA.     |
'--------------------------------------------------' */
int putchar ( int c );

/*
.--------------------------------------------------.
| puts | funzione che stampa una stringa           |
| in output. Prende come parametro il puntatore    |
| alla stringa, definita di sola lettura, quindi   |
| la funzione non potra' modificare 'str', e       |
| restituisce in un 'int' i numero dei caratteri   |
| scritti o l'esito negativo. Al suo interno       |
| per stampare il singolo carattere utilizza a sua |
| volta la funzione putchar.                       |
'--------------------------------------------------' */
int puts ( const char *str ) ;

#endif

/* EOF */


