/*
.---------------------------------------------------------.
|                                                         |
|                                                         |
|                                                         |
|                                                         |
|                      LIBC / STDIO                       |
|                                                         |
|                                                         |
|                                                         |
'---------------------------------------------------------' */

#include "stdio.h"

/*
.-----------------------------------------------------.
| stdarg.h | Per printf e altre funzioni variadiche   |
'-----------------------------------------------------' */
#include "stdarg.h"

/*
.-----------------------------------------------.
| stdint.h | Per la definizione di NULL         |
'-----------------------------------------------' */
#include "stdint.h"   

/*
.------------------.
| Estensione Posix | 
'------------------' */
// #include "unistd.h"

/*
.--------.          
| Kernel |
'--------' */
// #include "libk.h"


/* =============== STDIO | ANSI ================= */

/*
.--------------------------------------------------.
| puts | funzione che stampa una stringa in        |
|        output. Prende come parametro il          |
|        puntatore alla stringa, definita di sola  |
|        lettura, quindi la funzione non potra'    |
|        modificare 'str', e restituisce in un     |
|        'int' i numero dei caratteri scritti o    |
|        l'esito negativo. Al suo interno per      |
|        stampare il singolo carattere utilizza a  |
|        sua volta la funzione putchar.            |
'--------------------------------------------------' */
int puts ( const char *str )
{
     while (*str) {
        putchar(*str);
        str++;
     };
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
|           in output. Prende come parametro il    |
|           carattere da stampare e restituisce    |
|           l'esito dell'operazione. Al momento al |
|           suo interno scrive direttamente nella  |
|           memoria video VGA.                     |
'--------------------------------------------------' */
int putchar ( int c )
{
     vga_putchar(c);

     return 0;
}

/*
.--------------------------------------------------.
| putc    |                                        |
|                                                  |
|                                                  |
|                                                  |
|                                                  |
|                                                  |
'--------------------------------------------------' */
int putc ( int c, FILE *stream)
{
     return 0;
}

/*
.--------------------------------------------------.
| fflush |                                         |
|                                                  |
|                                                  |
|                                                  |
|                                                  |
|                                                  |
'--------------------------------------------------' */
int fflush ( FILE *stream )
{
     return 0;
}


/* ===================== categoria ======================= */

// NON STANDARD | Stampa un intero senza segno in base da 2 a 16

static int print_unsigned (unsigned int n, unsigned int base, int uppercase)
{
    static const char digits[] = "0123456789abcdef" ;
    static const char DIGITS[] = "0123456789ABCDEF" ;
      
    const char *alphabet = uppercase ? DIGITS : digits;

    char buffer[sizeof(unsigned int) * 8];

    int len = 0;
 
    int count = 0;

    do {

        buffer[len++] = alphabet[n % base];
        n /= base ;
    } while (n != 0);

    while (len > 0) {
        putchar(buffer[--len]);
        count++;
    }

    return count;
}

int printf (const char *format, ...)
{   

    /*
    .-----------------------------------------.
    | Definisce args come variabile che punta |
    | alla lista dei parametri anonimi.       |
    '-----------------------------------------' */
    va_list args ;

    int count = 0 ;

    /*
    .---------------------------------------------.
    | Inizializza la lista di parametri anonima,  |
    | posizionando 'args' al primo elemento.      |
    '---------------------------------------------' */  
    va_start(args, format);

    /*
    .-------------------------------------------------------------.
    | Legge il formato della stringa da visualizzarei al termine. |
    '-------------------------------------------------------------' */
    while (*format != '\0') {

        /*
        .----------------------------------------------------.
        | Legge finche' il carattere letto non rappresenta   | 
        | identificatore di un possibile elemento variabile  |
        | (carattere '%'), allora lo visualizza come         |
        | unsigned char, ed incrementa il contatore e        |
        | continua la lettura.                               | 
        '----------------------------------------------------' */
        if (*format != '%') {
            putchar((unsigned char)*format++);
            count++;
            continue;
        }

        /*
        .------------------------------------------.
        | continua a leggere la stringa di formato |
        '------------------------------------------' */ 
        ++format;

        /*
        .----------------------------------------------------------.
        | Se il formato e' terminato (0) esce dal ciclo di lettura |
        '----------------------------------------------------------' */
        if (*format == '\0')
            break;

        /*
        .-------------------------------------------------------.
        | Analizza cio' che trova dopo l'identificativo di una  |
        | possibile parte variabile (%) per capire se dovra'    |
        | gestire o meno una sostituzione.                      |
        '-------------------------------------------------------' */ 
        switch (*format++)
        { 
 
             /*
             .----------------------------------.
             | Stampa il carattere speciale '%' |
             '----------------------------------' */ 
             case '%': putchar('%');
                       count++;
                       break;

             /*
             .--------------------------------------------------------.
             | Carattere | Stampa il parametro anonimo come INT.      |
             '--------------------------------------------------------' */
             case 'c': putchar(va_arg(args,int));
                       count++;
                       break;

             /*
             .------------------------------------------------------.
             | Stringa | Stampa il parametro anonimo come PUNTATORE |
             '------------------------------------------------------' */
             case 's': {
                           const char *s = va_arg(args, const char *);
                           if (s==NULL)
                              s = "(null)";

                           while (*s != '\0') {
                              putchar((unsigned char)*s++);
                              ++count;
                           }
                           break;
                       }

             /*
             .-----------------------------------------------.
             | Numero | Stampa il parametro anonimo come INT |
             '-----------------------------------------------' */
             case 'd':
             case 'i': {
                           int value = va_arg(args, int);
                           unsigned int magnitude;
                           if (value < 0) {
                              putchar('-');
                              ++count;

                              /* evita l'overflow anche per INT_MIN. */ 
                              magnitude = 0u - (unsigned int)value;
                           }
                           else {
                              magnitude = (unsigned int)value;
                           }

                           count += print_unsigned(magnitude, 10, 0);
                       }

             case 'o': count += print_unsigned ( va_arg(args, unsigned int), 8, 0);
                       break;

             case 'x': count += print_unsigned ( va_arg(args, unsigned int), 16, 0);

             case 'X': count += print_unsigned ( va_arg(args, unsigned int), 16, 1);

             default : /* specifica non supportata : la mostra letteralmente */ 
                       putchar('%');
                       putchar((unsigned char)format[-1]);
                       count += 2;
                       break;
        }
    }

    /*
    .----------------------------------------------------------------.
    | Dichiara di aver concluso le letture della lista dei parametri |
    | anonimi, tramite la variabile args, dichiarata con la va_list  |
    '----------------------------------------------------------------' */  
    va_end(args);

    /*
    .-------------------------------------------.
    | Torna il numero di caratteri stampati.    |
    '-------------------------------------------' */
    return count;
} 

