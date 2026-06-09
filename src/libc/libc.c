/*
.---------------------------------------------------------.
|                                                         |
|                                                         |
|                                                         |
|                                                         |
|                          LIBC                           |
|                                                         |
|                                                         |
|                                                         |
'---------------------------------------------------------' */

#include "stdio.h"
#include "string.h"

/* =============== STDIO | ANSI ================= */
      
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
int puts ( const char *str ) 
{
     while (*str) { 
        putchar(*str);
        str++;
     }
/*
     int i = 0;
     while ( str[i] != '\0' ) {
             putchar(str[i]);
             i++;
     };
*/
     return 0; 
}

/*
.--------------------------------------------------.
| putchar | funzione che stampa un carattere       |
| in output. Prende come parametro il              |
| carattere da stampare e restituisce l'esito      |
| dell'operazione. Al momento al suo interno       |
| scrive direttamente nella memoria video VGA.     |
'--------------------------------------------------' */
int putchar ( int c )
{
     vga_putchar(c);  

     return 0;
}

/* ================= STRING ================ */

/*
.----------------------------------------------------.
| memcpy - serve essenzialmente per evitare che il   |
| compilatore traduca l'inizializzazione di un'      |
| array in una chiamata a memcpy, e che non trovi    |
| poi il simbolo.                                    |
'----------------------------------------------------' */
void *memcpy(void * dest, const void *src, size_t n)
{
     unsigned char *d = dest ;
     const unsigned char *s = src;

     while (n--)
        *d++ = *s++;

     return dest;    
}

/* :::... EOF */ 


