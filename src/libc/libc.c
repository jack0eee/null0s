/*
.---------------------------------------------------------.
|                                                         |
|                                                         |
|                                                         |
|                                                         |
|                         LIBC                            |
|                                                         |
|                                                         |
|                                                         |
'---------------------------------------------------------' */

#include "stdio.h"
#include "string.h"
#include "ctype.h"

/* =============== CTYPE | ANSI ================= */

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


/* ================= STRING (funzioni stringhe) ================ */

/*
.----------------------------------------------------.
| strlen | La funzione riceve l'indirizzo di memoria |
|          di una stringa da leggere fino al         |
|          carattere '\0' per determinare la sua     |
|          lunghezza. Come tutte le funzioni STRING  |
|          anche questa e' pericolosa se usata male. |
|          Se la fonte non e' controllata e          |
|          controllabile, allora *non* usatela, per  |
|          evitare poi dei buffer overflow.          |
'----------------------------------------------------' */
size_t strlen (const char *s) 
{
       size_t len = 0 ;

       while (s[len]!='\0')
       {
            len++;

         /* if (len > 4096)
          *    panic("strncat: stringhe non terminate, over 4k");
          */
       }

       return len;          
};
                               
/*
.----------------------------------------------------.
| strcmp | La funzione riceve l'indirizzo di memoria |
|          di due stringhe da verificare se sono     |
|          identiche, quindi le scorre entrambe      |
|          byte per byte, e appena si accorge che    |
|          per una posizione son differente, si      |
|          interrompe; oppure a terminazione della   |
|          prima stringa ricevuta (s1).              |
|          La funzione ritorna '0' se le due         |
|          stringhe son risultate uguali. Se le due  |
|          stringhe invece son risultate differenti  |
|          torna '-1' se alla posizione in cui le    |
|          stringhe son risultate differenti l'ascii |
|          presente in s1 e' minore del              |
|          corrispondente ascii corrisposndente      |
|          trovato in s2. E restituisce '+1' in caso |
|          opposto.                                  |
|                                                    |
|          Attenzione! Questa funzione non rispetta  |
|          pienamente lo standard, che vorrebbe, che |
|          in caso di differenza venisse restituito  |
|          la distanza ascii tra i 2 caratteri       |
|          trovati differenti. Quindi ci potrebbe    |
|          qualche software che sfrutta tale logica  |
|          anche se mi sembra una rarita'.           |
|          Sappiatelo!                               |
|                                                    |  
'----------------------------------------------------' */
int strcmp (const char *s1, const char *s2)
{
    // size_t len = 0 ;

       while (*s1 && (*s1==*s2)) 
       {
            s1++;
            s2++;

         /* len++:
          * if (len > 4096)
          *    panic("strncat: stringhe non terminate, over 4k");
          */ 
       }

       if (*s1<*s2)
          return -1;

       if (*s1>*s2)
          return +1;

       return 0;
};

/*
.----------------------------------------------------.
| strncmp| Rispetto alla funzione strcmp questa e'   |
|          di granlunga piu' sicura perche' pone un  |
|          limite per trovare il fine stringa        |
|          sorgente da copiare nella destinazione.   |
|          Se il limite e' superato senza aver       |
|          trovato il fine riga allora interrompe la |
|          copia. Quindi vi e' una doppia condizione |
|          e questo non e' poco. Se il limite e'     |
|          impostato a zero, esce immediatamente     |
|          senza copiare alcun byte dalla src alla   |
|          dst, e ritornando l'esito positico (0).   |
|          In tal caso nella dst non viene copiato   |
|          nemmeno il '\0', e qui bisogna stare      |
|          attenti, ma lo standard dice questo.      |
|          Ed in quetso caso mi ci attengo.          |
|                                                    |
|          Attenzione! Questa funzione non rispetta  |
|          pienamente lo standard, che vorrebbe, che |
|          in caso di differenza venisse restituito  |
|          la distanza ascii tra i 2 caratteri       |
|          trovati differenti. Quindi ci potrebbe    |
|          qualche software che sfrutta tale logica  |
|          anche se mi sembra una rarita'.           |
|          Sappiatelo!                               |
'----------------------------------------------------' */
int strncmp (const char *s1, const char *s2, size_t n)
{
      /* se viene impostata una lunghezza 0. Ritorna 0,
       * come se le stringhe fossero state uguali 
       */
       if (n==0) return 0;

      /* legge i 2 array byte-byte fintanto: 
       *  [1] non arriva un fine riga. 
       *  [2] le stringhe byte-byte son identiche
       *  [3] non si e' raggiunto la lunghezza limite
       */ 
       while (*s1 && (*s1==*s2) && n>1 ) {
             s1++;
             s2++;

             n--; 
       };

      /* confronta l'ultimo byte di s1 ed s2, 
       * se son differenti significa che le stringhe
       * stesse lo sono. Si limita restituire -1 o +1
       * in tal caso senza fornire la distanza precisa
       * --dell'ultimo byte-- nel caso in cui son differenti 
       * Oppure 0 se s1 ed s2 risultano identiche 
       */ 
       if (*s1<*s2)
          return -1;

       if (*s1>*s2)
          return +1;

       return 0;
}

/*
.----------------------------------------------------.
| strcpy | Questa funzione e' semplice, come del     |
|          resto tutte le funzioni di string. Riceve |
|          essenzialmente due puntatori a stringa:   |
|          una sorgente ed una destinazione. Quella  |
|          sorgente chiaramente e' di sola lettura.  |
|          La funzione legge la stringa sorgente     |
|          fino a che non trova il fine stringa '\0' |
|          e ogni byte che legge lo copia all'       |
|          indirizzo di memoria della stringa di     |
|          destinazione, ed avanza anche questo      |
|          puntatore. Cosa non verifica questa       |
|          funzione: che ci sia abbastanza spazio    |
|          per la stringa di destinazione. Pertanto  |
|          se l'origine dovesse arrivare senza fine  |
|          stringa questo causerebbe nel caso        |
|          un comportamente non voluto nel chiamante |
|          e nel caso peggiore un buffer overflow.   |
|          Mai usare la strcpy con stringa sorgente  |
|          che arriva dall'esterno, e non            |
|          preventivamente controllata. Per usi      |
|          interni l'utilizzo con valore controllato |
|          la si puo' tranquillamente utilizzare.    | 
|                                                    |
|          * while poco didattiva                    | 
|          * paranoic mode, rimando indeciso         |
|          * ho un dibbio sulla dest (const si/no)   |
|          * restrinct da C99 in poi (no C98)        |
|                                                    | 
'----------------------------------------------------' */
char *strcpy(char *restrict dest, const char *restrict src)
{
    // size_t len = 0 ;

      /* Copia l'indirizzo della stringa dest in un
       * puntatore di appoggio (d) e lavora di quello
       * per preservarne la posizione, per la return.
       */
       char *d=dest;   
                     
      /* Copia la stringa 'src' in 'd' (puntatore copia di dest)
       * a byte-byte fine a raggiungere il fine src '\0'
       * forma poco didattica.
       */ 
       while ((*d++=*src++)!='\0') { 

         /* len++:
          * if (len > 4096)
          *    panic("strncat: stringhe non terminate, over 4k");
          */
       }; 

       return dest;
}

/*
.----------------------------------------------------.
| strncpy| Rispetto alla funzione strcpy questa e'   |
|          di granlunga piu' sicura perche' pone un  |
|          limite per trovare il fine stringa        |
|          sorgente da copiare nella destinazione.   |
|          Se il limite e' superato senza aver       |
|          trovato il fine riga allora interrompe la |
|          copia. Quindi vi e' una doppia condizione |
|          e questo non e' poco. Se il limite e'     |
|          impostato a zero, esce immediatamente     |
|          senza copiare alcun byte dalla src alla   |
|          dst, e ritornando l'esito positico (0).   |
|          In tal caso nella dst non viene copiato   |
|          nemmeno il '\0', e qui bisogna stare      |
|          attenti, ma lo standard dice questo, ed   |
|          in questo caso mi ci attengo.             |
'----------------------------------------------------' */
char *strncpy(char *restrict dest, const char *restrict src, size_t n)
{
      /* Copia l'indirizzo della stringa dest in un 
       * puntatore di appoggio (d) e lavora con quello 
       * per preservarne la posizione iniziale, per la return.
       */
       char *d=dest; 
       
      /* Copia la stringa 'src' in 'd' (puntatore copia di dest) 
       * a byte-byte fintanto son valide queste 2 condizioni :
       * [1] non legge in src un carattere di fine stringa '\0'
       * [2] non raggiunge la lunghezza limite da copiare n>1
       * forma poco didattica
       */               
       while ((*d++=*src++)!='\0' && n>1) {              
             n--;
       };

       return dest;  
}

/*
.----------------------------------------------------.
| strcat | La funzione riceve due puntatori : str    |
|          origine e str di destinazione. Quel che   |
|          fa e' prima di tutto trovare la fine      |
|          della stringa di destinazione ('\0'), e   |
|          da quel punto inizia a copiare byte-byte  |
|          il valore di stringa sorgente in stringa  |
|          destinazione, sovrascrivendo il fine      |
|          stringa di destinazione. La stringa di    |
|          destinazione chiaramente terminera' con   |
|          il fine stringa dell'origine. Valgono     |
|          anche qui le medesime considerazioni      |
|          di sicurezza fatte per la strcpy.         |  
'----------------------------------------------------' */
char *strcat(char *restrict dest, const char *restrict src)
{
    // size_t len = 0 ;

      /* Copia l'indirizzo della stringa dest in un
       * puntatore di appoggio (d) e lavora di quello
       * per preservarne la posizione, per la return.
       */
       char *d=dest; 

      /* Si posizione alla fine di 'd' (fino a che non trova il fine stringa)
       * Il rischio e' che non lo trovi, o in posizione random  
       * esempio : "sotto\0" -> "sotto\0"
       *            ^                 ^ 
       */ 
       while (*d) {          
          d++;

         /* len++:
          * if (len > 4096)
          *    panic("strncat: stringhe non terminate, over 4k");
          */
       };

      /* inizia a concatenare alla destinazione, sovrascrivendo
       * il fine stringa di destinazione, la stringa sorgente
       * da concatenare fino a trovarne il fine stringa.
       * esempio : "sotto\0" -> "sottoterra\0" -> ret: "sottoterra\0"
       *                 ^                   ^          ^
       *                 d                   d          dest 
       */
       while ((*d++=*src++)!='\0'); 

       return dest;
}

/*
.----------------------------------------------------.
| strncat| Rispetto la funzione base strcat, questa  |
|          e' piu' sicura, ma rimane non sicurissima |
|          Oltre alla stringa di destinazione e      |
|          sorgente, riceve una lunghezza (n) di     |
|          byte massimi di src da concatenare a dest |
|          Questa e' una salvaguardia su src, ma non |
|          per dest, per la quale nel caso non       |
|          abbia un terminatore '\0' impostato       |
|          correttamente puo' andare a spazzolasi la |
|          memoria fino a raggiungere aree negate,   |
|          ed ottenere malfunzionamenti difficili    |
|          da interpretarne l'origine, o generare    |
|          dei bufferOverflow. Le strncat e' quella  |
|          piu' pericolosa tra le altre "strn*2".    |
|          Gli svilupattore OpenBSD ne hanno         |
|          sviluppata un po piu' sicura che e' la    |
|          "strlcat".                                |
|          Ritornando alla funzione, questa torna    |
|          dest immodificato se la 'n' vale 0,       |
|          perche' una delle 2 condizioni di uscita  |
|          e' gia' valida. In caso contrario (n>0)   |
|          salva il puntatore di dest in 'd' per     |
|          preservare la locazione di inizio, e      |
|          lavora su 'd'. Poi, si posizione alla     |
|          fine di 'd', ossia fini al terminatore    |
|          e poi da quella posizione, copia          |
|          byte-byte la src, fino a che rimangono    |
|          valide le seguenti 2 condizioni.          |
|          1) il byte src letto non e' '\0'          |
|          2) non abbiamo raggiunto il limite (n).   | 
'----------------------------------------------------' */
char *strncat (char *restrict dest, const char *restrict src, size_t n)
{
    // size_t len = 0 ;

      /* se viene impostata una lunghezza 0. Ritorna la stringa 
       * di destinazione senza far nulla (alcuna concatenazione). 
       */
       if (n==0) return dest;

      /* Copia l'indirizzo della stringa dest in un
       * puntatore di appoggio (d) e lavora di quello
       * per preservarne la posizione, per la return.
       */
       char *d=dest;

      /* Si posizione alla fine di 'd' (fino a che non trova il fine stringa)
       * Il rischio e' che non lo trovi, o in posizione random
       * esempio : "sotto\0" -> "sotto\0"
       *            ^                 ^
       */
       while (*d) {
          d++;

         /* len++:
          * if (len > 4096)
          *    panic("strncat: stringhe non terminate, over 4k");
          */
       };

      /* inizia a concatenare alla destinazione, sovrascrivendo
       * il fine stringa di destinazione, la stringa sorgente
       * da concatenare fino se sono vere entrambe le condizioni :
       * [1] non letto il fine stringa '\0'.
       * [2] non raggiunta la lunghezza limite di concatenazione (n>1)
       *
       * esempio-1 :
       *              dest         src        n    dest (return) 
       *             "sotto\0"    "terra\0"  20   "sottoterra\0"
       *             "sotto\0"    "terra\0"   3   "sottoter\0"
       */
       while ((*d++=*src++)!='\0' && n>1 ) {
             n--;
       };

       return dest;
}

/* ================= STRING (funzioni di ricerca e scansione) ================ */

/*
.----------------------------------------------------.
| strchr | Questa funzione e' semplice ma anche      |
|          molto utile. In sintesi, riceve           |
|          l'indirizzo di memoria di una stringa ed  |
|          carattere, e restuira' l'indirizzo di     |
|          memoria in cui questo carattere e' stato  |
|          trovato al'interno della stringa. Nel     |
|          caso in cui il carattere non venga        |
|          trovato restituisce NULL.                 |
|          Questa funzione e' ad esempio utile in    |
|          un semplice parser per suddividere ad     |
|          esempio il comando da i parametri,        |
|          separati da spazio.                       |
|          ---                                       |
|          char *comando = "ls -ltr /home/jacl0e" ;  |
|          strchr(comando, ' ');                     | 
|          *comando='\0';                            |
|          comando++;                                |
|          ---                                       |
|          comando : "ls\0-ltr /home/jack0e"         |
|                         ^                          |
|                         '--- puntatore             |
'----------------------------------------------------' */
char *strchr (const char *s, int c)
{
    // size_t len = 0 ;

       while(*s)  
       {
          if (*s==(char)c)
             return (char *)s;
         
          s++;

          // len++;
          // if (len > 4096)
          //    panic("strchr: stringhe non terminate, over 4k");
       } 

       if (c=='\0')
          return (char *)s;

       return NULL;
}

/*
.----------------------------------------------------.
| strrchr| ultima posizione in cui trova 'c'.        |
|          scorre tutta la stringa e tiene traccia   |
|          dell'ultima posizione in cui ha trovato   |
|          il carattere ricercato (c). Ritorna il    |
|          puntatore o NULL se non trovato.          |
'----------------------------------------------------' */
char *strrchr(const char *s, int c)
{
    // size_t len = 0 ;

      /*
       * Ultima posizione in cui e' stato trovato
       * nella stringa il carattere da ricercare.
       * ss e' dichiarato come size_t che possa contenere
       * la massima locazione di memoria indirizzabile.
       * Viene inizializzato a NULL (utilizzando il cast size_t) */
       size_t ss = (size_t)NULL; 

      /*
       * Si scorre dall'inizio tutta la strinfa s, fino 
       * al carattere di fine stringa '\0'. Se trova il carattere
       * da ricercare durante la lettura, conserva in ss la sua posizione
       * sempre effettuando il medesimo cast, e continua a leggere s. */ 
       while(*s)
       {
          if (*s==(char)c)
             ss = (size_t)s ;

          s++;

          // len++;
          // if (len > 4096)
          //    panic("strrchr: stringhe non terminate, over 4k");
       }

      /* Al termine della lettura di s, restituisce l'indirizzo di memoria
       * memorizzato da ss. Se il carattere non e' stato trovato contiene 
       * il NULL iniziale, con cui e' stato inizializzato. Altrimenti
       * l'indirizzo di memoria dell'ultima posizione in s in cui il
       * carattere da ricercare (c) e' stato trovato */
       return (char *)ss ;
}

/*
.----------------------------------------------------.
| strstr | cerca una sottostringa (needle) in una    |
|          stringa (haystack). Se la sottostringa    |
|          da ricercare e' vuota '' torna il         |
|          puntatore alla stringa haystack.          |
|                                                    |
|          POSSIBILE OTTIMIZZAZIONE!!!!!!!!!!!!!!    |
|          Cio' che non viene testato, invece e'     |
|          che la lunghezza di 'needle' non sia      |
|          maggiore di 'haystack', in questo caso    |
|          sarebbe inutile cercare una sottostringa  |
|          piu' grande di una stringa. Cosi come     |
|          non ha piu' senso cercare una sottostring |
|          quando rimane da analizzare una parte     |
|          della stringa con lunghezza minore.       |
'----------------------------------------------------' */
char *strstr (const char *haystack, const char *needle)
{
    // size_t len_haystack = 0 ;
    // size_t len_needle   = 0 ;

      /*
       * Fa una copia degli indirizzi iniziali di memoria
       * di haystack e needle per poterli preservare, ed 
       * utilizzare le copie */
       const char *h = haystack ;
       const char *n = needle ;

      /*
       * Se la sottostringa da ricercare (needle) e'
       * vuota, esce immediatamente restituendo  
       * la stringa haystack */
       if ( *needle == '\0' )
          return (char *)haystack ;

      /* 
       * Entra nel ciclo di lettura di stringa e sottostringa
       * fintanto una delle 2 trova un fine stringa. */
       while (*h && *n)
       {
            /* Inizia il confronto byte-byte */
             if ( *h == *n )
             {
                  /* Se ha trovato un byte identico tra
                   * stringa e sottostringa, continua  
                   * a scorrere la sottostringa. */ 
                   n++;
             }
             else
             {
                  /* Se ha trovato un byte differente, 
                   * riposiziona la sottostringa al suo inizio
                   * ripristinando il valore originale */
                   n = needle ;

                // len_needle = 0 ; 
             }

             h++;

          // len_haystack++;
          // len_needle++;
          // if (len_haystack > 4096 || len_needle > 4096)
          //    panic("strstr: stringhe non terminate, over 4k")
       }

      /* Trovata needle
       * Posiziona il puntatore haystack all'inizio della sottostringa (needle) 
       * Per far questo calcola la lunghezza della sottostringa: n - needle 
       * e poi la sottrae al al valore attuale del puntatore ad haystack. */ 
       if ( *n == '\0' ) {
          h = h - ( n - needle ); 
       }

      /* Non trovata needle 
       * Ripristina il puntatore haystack all'inizio della stringa  */
       if ( *n != '\0' ) {
          h = haystack ;
       }
 
       return (char *)h;  
}

/*
.----------------------------------------------------.
| strpbrk| cerca il primo carattere appartenente ad  |
|          un set. E' un po' simile alla strchr, ma  |
|          anziche' cercare il singola carattere, ne |
|          cerca piu' di uno fermandosi al primo     |
|          trovato nella stringa tra quelli buoni    |
|          (accettati, accept). Se nella stringa non |
|          ne trova nessuno, allora restituisce,     |
|          NULL (come la strchr). La funzione scorre |
|          entrambe le string (s ed accept) fino a   |
|          trovare il carattere di fine stringa '\0' |
'----------------------------------------------------' */
char *strpbrk (const char *s, const char *accept)
{
    // size_t len_s = 0 ;
    // size_t len_a = 0 ;

      /*
       * Fa una copia dell'indirizzo iniziale di memoria
       * di accept per poterlo preservare, ed
       * utilizzarne la copia (a) */
       const char *a = accept ;

      /*
       * Ciclo di lettura della stringa 's' fino
       * a che non trova un carattere di fine stringa '\0' */
       while(*s)
       { 
         /* 
          * Per ogni carattere letto di 's', inizia un ciclo di lettura
          * dell'array 'accept' fino a che non trova anche qui il 
          * carattere di fine stringa '\0'. Se trova il fine stringa significa
          * che nessun carattere accettato e' stato trovato, quindi riposiziona
          * il puntatore all'inizio di accept e si prepara a leggere il carattere
          * successivo di 's'. Se invece il carattere letto di 's' e' 
          * uguale ad uno dei caratteri accettati, eve immediatamente
          * dalla funzione restituendo il puntatore/locazione di memoria
          * attuale di 's'. */
          while (*a)
          {
               if (*s==*a)
                   return (char *)s;

               a++;

            // len_s++;
            // if (len_a > 4096)
            //    panic("strpbrk: stringa (accept) non terminata, over 4k");

          }
          a = accept ;

          s++;

          // len_s++;
          // if (len_s > 4096)
          //    panic("strpbrk: stringa (s) non terminata, over 4k");
       }

       return NULL;
}

/*
.----------------------------------------------------.
| strspn | conta quanto inizio di stringa e' letto   |
|          solo incontrando caratteri validi. Si     |
|          ferma al primo carattere non valido,      |
|          cioe' non presente nell'insieme degli     |
|          accettati, oppure a fine stringa, nel     |
|          caso siano tutti in tale insieme. La      |
|          funzione torna quanti caratteri son       |
|          risultati validi fino all'interruzione.   |
'----------------------------------------------------' */
size_t strspn (const char *s, const char *accept)
{
    // size_t len_s = 0 ;
    // size_t len_a = 0 ;

      /*
       * Contatore dei caratteri della stringa 's'
       * presenti nell'insieme dei caratteri accettati */
       size_t count_accept = 0;

      /*
       * Fa una copia dell'indirizzo iniziale di memoria
       * di accept per poterlo preservare, ed
       * utilizzarne la copia (a) */
       const char *a = accept ;
       
      /*
       * Ciclo di lettura della stringa 's' fino
       * a che non trova un carattere di fine stringa '\0' */
       while(*s)
       {
         /*
          * Per ogni carattere letto di 's', inizia un ciclo di lettura
          * dell'array 'accept' fino a che non trova anche qui il
          * carattere di fine stringa '\0'. Esce dal ciclo di letture, 
          * per due condizioni: [1] se trova il fine stringa 
          * [2] se trova che il carattere della stringa (s) appartiene
          * all'insieme dei caratteri accettati. */ 
          while (*a || *s==*a)
          {
               if (*s!=*a)
                   a++;

            // len_s++;
            // if (len_a > 4096)
            //    panic("strspn: stringa (accept) non terminata, over 4k");

          }

         /* Quando il ciclo di lettura termina per uno dei due motivi, sopra elencati 
          * eseguo la verifica che accerta che il carattere di 's' analizzato
          * non appartiene all'insieme dei caratteri accettati. In tal caso 
          * esce dalla funzione restituendo il numero accettati fino a quel 
          * momento letti, della stringa s.  */
          if (*a == '\0' && *s != *a)
               return count_accept ; 

         /* Incrementa il contatore dei caratteri di 's' nell'insieme 
          * di quelli accettati */
          count_accept++;

         /* Se mi trovi qui, tutto procede: ogni carattere letto della stringa
          * appartiene all'insieme dei caratteri accettati, quindi: ripristina
          * il puntatore di accept e si prepara a leggere il carattere
          * successivo della stringa (s) */ 
          a = accept ;

          s++;

          // len_s++;
          // if (len_s > 4096)
          //    panic("strspn: stringa (s) non terminata, over 4k");
       }

       return count_accept;
}

/*
.----------------------------------------------------.
| strcspn| conta quanto inizio di stringa e' letto   |
|          solo incontrando caratteri validi. Si     |
|          ferma al primo carattere non valido,      |
|          cioe' presente nell'insieme dei caratteri |
|          non accettati (reject), oppure a fine     |
|          stringa, nel caso nessun sia in tale      |
|          insieme. La funzione torna quanti         |
|          caratteri son risultati validi, fino      |
|          all'interruzione.                         |
'----------------------------------------------------' */
size_t strcspn (const char *s, const char *reject)
{
    // size_t len_s = 0 ;
    // size_t len_r = 0 ;

      /*
       * Contatore dei caratteri della stringa 's'
       * non presenti nell'insieme dei caratteri 
       * non accettati (reject) */
       size_t count_accept = 0;

      /*
       * Fa una copia dell'indirizzo iniziale di memoria
       * di accept per poterlo preservare, ed
       * utilizzarne la copia (a) */
       const char *r = reject ;

      /*
       * Ciclo di lettura della stringa 's' fino
       * a che non trova un carattere di fine stringa '\0' */
       while(*s)
       {
         /*
          * Per ogni carattere letto di 's', inizia un ciclo di lettura
          * dell'array 'reject' fino a che non trova anche qui il
          * carattere di fine stringa '\0'. Esce dal ciclo di letture,
          * per due condizioni: [1] se trova il fine stringa
          * [2] se trova che il carattere della stringa (s) appartiene
          * all'insieme dei caratteri *non* accettati (r). */
          while (*r && *s!=*r)
          {
               if (*s!=*r)
                   r++;

            // len_r++;
            // if (len_r > 4096)
            //    panic("strcspn: stringa (reject) non terminata, over 4k");

          }

         /* Quando il ciclo di lettura termina per uno dei due motivi, sopra elencati,
          * eseguo la verifica che accerta che il carattere di 's' analizzato
          * appartenga all'insieme dei caratteri non accettati (reject). In tal caso
          * esce dalla funzione restituendo il numero di caratteri che 
          * fino a quel momento son stati letti, e son risultati validi. */
          if (*r != '\0' && *s == *r)
               return count_accept ;

         /* Incrementa il contatore dei caratteri di 's' nell'insieme
          * di quelli accettati */
          count_accept++;

         /* Se mi trovi qui, tutto procede: ogni carattere letto della stringa
          * non appartiene all'insieme dei caratteri non validi (reject), 
          * quindi: ripristina il puntatore di reject e si prepara a leggere 
          * il carattere successivo della stringa (s) */
          r = reject ;

          s++;

          // len_s++;
          // if (len_s > 4096)
          //    panic("strcspn: stringa (s) non terminata, over 4k");
       }

       return count_accept;
}


/* ======== STRING (tokenizzazione) ========================== */
/* =============== SONO QUI ================ */
/*
.----------------------------------------------------.
| strtok | viene passato l'indirizzo alla stringa s  |
|          e alla stringa di delimitazione. Lo scopo |
|          della funzione e trovare la sottostringa  |
|          alla sinistra del delimitatore passato.   |
|                                                    | 
|          Es. s="mele, pere, limoni\0" - delim=", " |         
|                                                    |
|          Se trova il delimitatore, sostituisce     |
|          questo con un carattere di fine stringa   |
|          e restituisce il puntatore ad inizio      |
|          stringa s.                                |
|                                                    |
|          Es. s="mele\0pere, limoni\0"              | 
|                 ^                                  |
|          Per trovare i successivi token, va        |
|          rieseguita la funzione, impostando come   |
|          stringa non piu' il puntatore s, ma NULL. |
|                                                    |
|          Es. strtok (NULL, delim); // delim=", "   |
|                                                    | 
|          La funzione cerchera' il delimitatore     |
|          dal primo carattere di fine stringa in    |
|          fino al delimitatore o alla fine stringa  |
|          tornando il puntatore al successivo       |
|          token.                                    |
|                                                    |
|          Es. s="mele\0pere\0, limoni\0"            |
|                       ^                            |
|          Al terza esecuzione, strtok restituira'   |
|          il puntatore al terzo token.              |
|                                                    |
|          Es. s="mele\0pere\0limoni\0"              |
|                             ^                      |
|          Se rieseguita, restituira' da quel        |
|          momento in poi NULL, che significa che i  |
|          token son finiti                          |
|                                                    |
|          Si deduce quanto :                        |
|                                                    |
|          Se il delimitatore non viene trovato, il  |
|          token e' delimitato quindi dal carattere  |
|          di fine stringa '\0'.                     |
|                                                    |
|          Casi particolare :                        |
|                                                    |
|          - Stringa Vuota o con soli delimitatori   |
|                                                    |
|          Ritorna NULL                              |
|                                                    | 
'----------------------------------------------------' */
char *strtok (char *s, const char *delim)
{
 
      return s;
}


/* ======== STRING (gestione errori) =================================== */

/*
.----------------------------------------------------.
'----------------------------------------------------' */
char *strerror (int errnum)
{
      return 0;
}


/* ======== STRING (funzioni su memoria grezza | ignorano il terminatore '\0') ======== */

/*
.-------------------------------------------------------------.
| memcpy | serve essenzialmente per evitare che il            |
|          compilatore traduca l'inizializzazione di un'      |
|          array in una chiamata a memcpy, e che non trovi    |
|          poi il simbolo. All'inizio dello sviluppo del      |
|          e' stata la prima funzione di libc creata per      |
|          quetso motivo. :-)                                 |
|          La funzione e' un'alternativa a strcpy, ma *molto* |
|          piu' sicura, ed e' consigliato tra le due,         |
|          utilizzare questa (quando si puo') perche' impone  |
|          al fratello sviluppatore di fornire anche la       |
|          lunghezza della stringa da copiare, quindi         |
|          l'operazione di copia non equivale ad una lettura  |
|          dell'array fino a trovare il carattere di          |
|          terminazione '\0'.                                 | 
'-------------------------------------------------------------' */
void *memcpy(void * dest, const void *src, size_t n)
{
     unsigned char *d = dest ;
     const unsigned char *s = src;

     while (n--)
        *d++ = *s++;

     return dest;    
}; 

/*
.----------------------------------------------------.
| memset | La funzione scrive un carattere ASCII     |
|          base [0..255] nell'aria di memoria        |
|          puntata da *s, per n volte. Quel che fa   |
|          e' conservarsi la locazione iniziale di   |
|          memoria, copiando tale indirizzo in p, e  |
|          lavorando su di osso. Questa viene        |
|          definito 'unsigned char', in maniera      |
|          tale da spostarsi di un byte per volta    |
|          per la dimensione di n. In ogni byte      |
|          posizionato, ci muove 'c' anch'esso con   |
|          il cast ad unsigned char. Se il valore c  |
|          passato non rientra nell'unsigned char    |
|          ossia 0-255, il cast lo riporta in questo |
|          range :                                   |
|          esempio-1 : se c = 300 -> c =c%255=45     |
|          esempio-2 : se c = -1  -> c =255          |
|          esempio-3 : se c = -2  -> c =254          |
|          La funzione ritorna sempre il puntatore   |
|          di memoria s, ricevuto in input.          | 
'----------------------------------------------------' */
void *memset(void *s, int c, size_t n)
{
     unsigned char *p = s ;

     while (n--)
        *p++ = (unsigned char)c ;

     return s;
}; 

/*
.----------------------------------------------------.
| memmove|copia src in dest per n byte. A differenza |
|         di memcpy in cui le due area di memoria:   |
|         src e dest non si sovrappongono, con       |
|         memmove possono anche sovrapporti, e'      |
|         capace di gestire tale scenario. memcpy e' |
|         piu' veloce, quindi se le aree non si      |
|         sovrappongono conviene utilizzare memcpy.  |
|         esempio:                                   |
|                  char s[] = "12345678";            |
|                  memmove (s+2, s, 4);              |
|                  return : "121234"                 |
|                                                    |
|         In una situazione del genere, la memcpy    |
|         dichiara "stato indefinito", cioe' lo      |
|         definisce il comportamento e quindi ogni   |
|         implementazione potrebbe comportarsi       |
|         in maniera differe. Con alcune potrebbe    |
|         funzionare e con altre no.                 |
|         Per preservare l'src (perche' e' questo    |
|         rischia la perdita di dati in caso di      |
|         sovrapposizioni) viene salvato altrove, e  |
|         poi copiato in dest. Quindi dal punto di   |
|         vista concettuale e come se la memmove :   |
|         *  memmove (src, dest, n)                  |
|         traducesse in due strcpy:                  |
|         1) memcpy (src    , src-app, n);           |
|         2) memcpy (src-app, dest   , n);           |
|                                                    |
|         Se (n)>0 && src>dest                       |
|            copia byte-byte di src->dest in avanti. |
|            (come se esguisse una nosrmale memcpy)  |
|                                                    |
|         Se (n)<0  la funzione effettua la          |
|                                                    |
|         Se (n)==0 la funzione arriva direttamente  |
|            al return di dest, senza far nulla.     |
'----------------------------------------------------' */
void *memmove(void *dest, const void *src, size_t n)
{
     unsigned char *d = dest ;
     const unsigned char *s = src;

    /*
     * se src > dest copia in avanti (come una normale memcpy) */
     if ( src > dest ) 
        while (n--)
           *d++ = *s++;

    /*
     * se src < dest copia all'indietro, maniera tale che
     * in questo caso non vi sia perdita di dati in src
     * Prendiamo l'esempio :
     *
     * memmove (src, dest, 3);
     *
     * supponiamo che src inizi a 1 byte in avanti rispetto ad 'src"
     *                        
     *      .-------------- indirizzo dest (src-2) 
     *      | .------------- indirizzo src  (desc+2)
     *      | V  
     * d |  V *;
     * s |  12345678  
     *                  
     * solo effettuando la copia al contrario, cioe' dalla cosa alla testa
     * si salvaguardia il contenuto di src.
     *
     *      .-------------- indirizzo dest (src-2)
     *      | .------------ indirizzo src  (desc+2)
     *      | V 
     * d |  V 123;
     * s |  12345678  
     *      <-* 
     */

     if ( src < dest ) 
     {
        d=d+(n-1); /* ultimo byte della destinazione */ 
        s=s+(n-1); /* ultimo byte della sorgente     */

        while (n--)
           *d-- = *s--;
     }
 
     return dest;
}; 

/*
.----------------------------------------------------.
| memcmp | Rispetto alla funzione strcmp questa e'   |
|          di granlunga piu' sicura perche' pone un  |
|          limite per trovare il fine stringa (s1)   |
|          da confrontare con l'altra stringa (s2).  |
|          Se il limite e' superato senza aver       |
|          trovato differenze allora si interrompe.  |
|          Oppure si interrompe alla prima           |
|          differenza. Quindi e' presente una doppia |
|          condizione, e questo non e' poco. Se il   |
|          limite e' impostato a zero, esce          |
|          immediatamente ritornando l'esito         |
|          positivo (0), come da standard.           |
|                                                    |
|          Attenzione! Questa funzione non rispetta  |
|          pienamente lo standard, che vorrebbe, che |
|          in caso di differenza venisse restituito  |
|          la distanza ascii tra i 2 caratteri       |
|          trovati differenti. Quindi ci potrebbe    |
|          qualche software che sfrutta tale logica  |
|          anche se mi sembra una rarita'.           |
|          Sappiatelo!                               |
'----------------------------------------------------' */
int memcmp (const void *s1, const void *s2, size_t n)
{
     /*
      * Rendo 's1' ed 's2' entrambi unsigned char, per poterli
      * confrontare. Il void e' difficile castarlo e 
      * potrei farlo anche nel ciclo, ma sarei costretto
      * ad eseguire il cast ad ogni ciclo, mentre metterlo
      * fuori esegue il cast una sola volta
      */
      const unsigned char *p1 = s1 ;
      const unsigned char *p2 = s2 ;

     /* se viene impostata una lunghezza 0. Ritorna 0,
      * come se le stringhe fossero state uguali */
      if (n==0) return 0;

     /* legge i 2 array byte-byte fintanto:
      * [1] le stringhe byte-byte son identiche
      * [2] non si e' raggiunto la lunghezza limite */
      while ((*p1==*p2) && n>1 ) {
           s1++;
           s2++;
           n--;
      };

     /* confronta l'ultimo byte di s1 ed s2,
      * se son differenti significa che le stringhe
      * stesse lo sono. Si limita restituire -1 o +1
      * in tal caso senza fornire la distanza precisa
      * --dell'ultimo byte-- nel caso in cui son differenti
      * Oppure 0 se s1 ed s2 risultano identiche
      */
      if (*p1<*p2)
         return -1;

      if (*p1>*p2)
         return +1;

      return 0;
}; 

/*
.----------------------------------------------------.
| memchr | Questa funzione e' semplice ma anche      |
|          molto utile. In sintesi, riceve           |
|          l'indirizzo di memoria di una stringa ed  |
|          carattere, e restuira' l'indirizzo di     |
|          memoria in cui questo carattere e' stato  |
|          trovato al'interno della stringa. Nel     |
|          caso in cui il carattere alla posizione   |
|          limite (n), non venga trovato restituisce |
|          il puntatore NULL.                        |
|          Simile alla funzione strchr, con la       |
|          differenza che memchr lavora su memoria   |
|          grezza, non tiene conto dei fine stringa  |
|          '\0' ma di una lunghezza limite (n).      | 
|          Questa funzione e' ad esempio utile in    |
|          un semplice parser per suddividere ad     |
|          esempio il comando da i parametri,        |
|          separati da spazio.                       |
|          ---                                       |
|          char *comando = "ls -ltr /home/jack0e" ;  |
|          memchr(comando, ' ', 20);                 |
|          ---                                       |
|          comando : "ls -ltr /home/jack0e"          |
|                        ^                           |
|                        '--- puntatore              |
|          ---                                       |
|          Se n e' zero ritorna NULL                 |
|          Se n e' negativo (ad esempio -1) il       |
|             cast lo conferte in un valore molto    |
|             grande. Nel caso specifico al massimo  |
|             valore di size_t (ad esempio FFFFFFFF) |
|             Questo e' un rischio.                  |
|             domanda? standard o difensiva?         | 
'----------------------------------------------------' */
void *memchr(const void *s, int c, size_t n)
{
     /*
      * Rendo 's' e 'c' entrambi unsigned char, per poterli
      * confrontare. Il void e' difficile castarlo e per 'c'
      * potrei farlo anche nel ciclo, ma sarebbe costretto
      * ad eseguire il cast ad ogni ciclo, mentre metterlo
      * fuori esegue il cast una solavolta 
      */
 
      const unsigned char *p = s ;
      unsigned char ch = (unsigned char)c ;

      while (n--) 
      {
          if ( *p == ch )
             return (void *)p ;

          p++;
      }

      return NULL;
}

/* :::... EOF */ 


