/*
.---------------------------------------------------------.
|                                                         |
|                                                         |
|                                                         |
|                                                         |
|                       LIBC / CTYPE                      |
|                                                         |
|                                                         |
|                                                         |
'---------------------------------------------------------' */

#include "ctype.h"

/*
.--------------------------------------------------.
| isdigit | il carattere e' un numero, cioe'       |
|           compreso tra 0 e 9 ? Restituisce 0     |
|           se e' false ed 1 se e' vero.           | 
'--------------------------------------------------' */
int isdigit (int c)
{
    if ( c >= '0' && c <= '9' ) 
    { 
         return 1 ;
    }
    else 
    {
         return 0 ;
    };
};

/*
.--------------------------------------------------.
| isalpha | il carattere e' un alfabetico, cioe'   |
|           compreso tra 'a' e 'z' o tra 'A' e 'Z' |
|           Restituisce 0 se e' falso ed 1 se e'   |
|           vero.                                  |
'--------------------------------------------------' */
int isalpha (int c)
{
    if (( c >= 'a' && c <= 'z' ) || 
        ( c >= 'A' && c <= 'Z' )) 
    {
         return 1 ;
    }
    else   
    {
         return 0 ;
    };
};

/*
.--------------------------------------------------.
| isalnum | Il carattere e' alfanumerico : numero  |
|           o un carattere alfabetico, ossia       |
|           compreso tra 'a' e 'z' oppure tra 'A'  |
|           e 'Z', oppure ancora tra '0' e '9'.    |
|           Se questa condizione e' falsa la       |
|           funzione restituisce 0, se e' vera     |
|           restituisce 1.                         |
'--------------------------------------------------' */
int isalnum (int c)
{
    if (( c >= 'a' && c <= 'z' ) || 
        ( c >= 'A' && c <= 'Z' ) ||
        ( c >= '0' && c <= '9' ))
    {
         return 1 ;
    }
    else  
    {
         return 0 ;
    };
};

/*
.--------------------------------------------------.
| isspace | Il carattere e' uno spazio o comunque  |
|           ricondotto ad esso, dal C. Quindi :    |
|                                                  |
|           nome             carattere    ascii    |
|           -----------------------------------    |
|           space            ' '           (32)    | 
|           tab orizzontale  '\t'           (9)    |
|           nuova riga       '\n'          (10)    |
|           tab verticale    '\v'          (11)    |
|           form feed        '\f'          (12)    |
|           carriage return  '\r'          (13)    | 
|                                                  |
'--------------------------------------------------' */
int isspace (int c)
{
    if ( c == ' '  || 
         c == '\t' ||
         c == '\n' ||
         c == '\v' ||
         c == '\f' || 
         c == '\r' )
    {
         return 1 ;
    }
    else
    {
         return 0 ;
    };
};

/*
.--------------------------------------------------.
| islower | il carattere e' un alfabetico          |
|           minuscolo, cioe' compresso tra 'a' e   |
|           'z'. Restituisce 0 se e' falso e 1 se  |
|           vero.                                  |
'--------------------------------------------------' */
int islower (int c)
{
    if ( c >= 'a' && c <= 'z' ) 
    {
         return 1 ;
    }
    else
    {
         return 0 ;
    };
};

/*
.--------------------------------------------------.
| isupper | il carattere e' un alfabetico          |          
|           maiuscolo, cioe' compresso tra 'A' e   |          
|           'Z'. Restituisce 0 se e' falso e 1 se  |           
|           vero.                                  |
'--------------------------------------------------' */
int isupper (int c)
{
    if ( c >= 'A' && c <= 'Z' ) 
    {
         return 1 ;
    }
    else
    {
         return 0 ;
    };
};

/*
.--------------------------------------------------.
| isxdigit | il carattere e' in numero esadecimale |
|            ossia compreso da '0' a '9', oppure   |
|            da 'a' a 'f', oppure da 'A' ad 'F'.   |
|            Insomma che sia all'interno di questo |
|            set : '0123456789ABCDEFabcdef'.       |
|            Restituisce 0 per falso ed 1 se vero. | 
'--------------------------------------------------' */
int isxdigit (int c)
{
    if (( c >= '0' && c <= '9' ) ||
        ( c >= 'A' && c <= 'F' ) ||
        ( c >= 'a' && c <= 'f' ))
    {
         return 1 ;
    }
    else
    {
         return 0 ;
    };
};

/*
.--------------------------------------------------.
| isprint | Verifica che sia un carattere          |
|           stampabile, ossia, in ASCII, compreso  |
|           tra lo spazio (32) e tilde (~)(126).   |
|           Restituisce 0 per falso ed 1 se vero.  |
'--------------------------------------------------' */
int isprint (int c)
{
    if ( c >= ' ' && c <= '~' )
    {
         return 1 ;
    }
    else
    {
         return 0 ;
    };
};

/*
.--------------------------------------------------.
| isgraph | Verifica che sia un carattere          |
|           visibile, ossia, in ASCII, compreso    |
|           tra lo spazio (32) e tilde (~)(126) :  |
|           A differenza di isprint(), esclude lo  |
|           spazio, perche' non visibile.          |
|           Restituisce 0 per falso ed 1 se vero.  |
'--------------------------------------------------' */
int isgraph (int c)
{
    if ( c > ' ' && c <= '~' )
    {
         return 1 ;
    }
    else
    {
         return 0 ;
    };
};

/*
.--------------------------------------------------.
| iscntrl | Verifica se e' un carattere di         |
|           controllo, quindi compreso da 0 a 31,  |
|           o 127 (DEL). Restituisce 1 se e' vero  |
|           e 0 se e' falso.                       |
'--------------------------------------------------' */
int iscntrl (int c)
{
    if (( c >= 0 && c <= 31 ) || c == 127 )
    {
         return 1 ;
    }
    else
    {
         return 0 ;
    };
};

/*
.--------------------------------------------------.
| ispunct | Verifica che sia un segno di           |
|           puntegiatura, quindi :                 |
|                                                  |
|           * stampabile           32..126 (~)     |
|           * non uno spazio.      32              | 
|           * non un numero        48..57  (0-9)   | 
|           * non una lettera (M)  65..90  (A-Z)   |
|           * non una lettera (m)  97..122 (a-z)   |
|                                                  |
|           pertanto: 33-47, 58-64, 91-96          |
|           i range in cui e' definita la          |
|           punteggiatura.                         |
|                                                  |
|           Restuisce 1 se la condizione e' vera   |
|           o 0 se la condizione e' falsa.         |
'--------------------------------------------------' */
int ispunct (int c)
{
    if (( c > ' ' && c <= '~' ) &&
        ( c < 'a' || c  > 'z' ) && 
        ( c < 'A' || c  > 'Z' ) &&
        ( c < '0' || c  > '9' )) 
       return 1 ;
    
    return 0;
};

/*
.--------------------------------------------------.
| isblank | (+++add C99) Verifica che sia uno      |
|           uno spazio orizzontale : ' ' o '\t'.   |
|           Restituisce 0 per falso ed 1 se vero.  |
'--------------------------------------------------' */
int isblank (int c)
{
    if ( c == ' '  || c == '\t' ) 
    {
         return 1 ;
    }
    else
    {
         return 0 ;
    };
};

/*
.--------------------------------------------------.
| tolower | Se il carattere e' alfabetico          |
|           maiuscolo, ossia compreso tra 'A' e    |
|           'Z', restituisce il corrispondente     |
|           minuscolo. In caso contrario ritorna   |
|           il carattere ricevuto.                 |
|           La distanza tra maiuscolo e minuscolo  |
|           e' 32, nella tabella dei codici ASCII. |
'--------------------------------------------------' */
int tolower (int c)
{
    if ( c >= 'A' && c <= 'Z' )
         return c + 32 ;
    
    return c;
};

/*
.--------------------------------------------------.
| toupper | Se il carattere e' alfabetico          |
|           minuscolo, ossia compreso tra 'a' e    |
|           'z', restituisce il corrispondente     |
|           minuscolo. In caso contrario ritorna   |
|           il carattere ricevuto.                 |
|           La distanza tra minuscolo e maiuscolo  |
|           e' -32, nella tabella codici ASCII.    |
'--------------------------------------------------' */
int toupper (int c) 
{
    if ( c >= 'a' && c <= 'z' )
         return c - 32 ;
    
    return c;
};

/* ================= CTYPE (funzioni stringhe) ================ */

