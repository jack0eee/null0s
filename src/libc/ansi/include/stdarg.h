/*
.----------------------------------------------------------------.
|        libc/include/ansi/stdarg.h | Funzioni Variadiche        |
+----------------------------------------------------------------+
| La stdarg.h sono una serie di macro per l'implementazione di   |
| funzioni variadiche, ossia di funzioni che accettano almeno    |
| un parametro noto, a cui possonono seguire un elenco di altri  |
| parametri indefiniti per numero.                               |
|                                                                |
| Tramite le 5 macro : va_list, va_start, va_arg, va_end e       |
| va_copy e' possibile leggere i valori dei parametri anonimi.   |
| Ad esempio una variabile variadica e' sicuramente la printf    |
| che presenta come primo parametri il formato e a seguire tutti |
| gli eventuali parametri che concorrono alla stringa da         |
| visualizzare.                                                  |
|                                                                |
| int d = 1 ;                                                    |
| char *descrizione = "FIAT 1100";                               |
| printf("Lista parametri %d | %s", codice, descrizione);        |
|                                                                |
| Visualizzato :                                                 |
| Lista parametri 1 | FIAT 1100                                  |
|                                                                |
| Una funzione variadica nel suo prototipo, dichiara i soli      |
| parametri noti, seguita da elissi "..." (tre punti)            |
|                                                                |
| >> MACRO :                                                     | 
|                                                                |
| va_list  | Server a definire una variabile che puntera' agli   |
|          | argomenti anonimi della lista.                      |
|          |                                                     | 
| va_start | inizializza la variabile definita da va_list, in    |
|          | modo tale che punti alla prima variabile anonima    |
|          | della lista.                                        |
|          |                                                     |
| va_arg   | restituisce il valore della lista anonima a cui     |
|          | la variabile definita da va_lista ed inizializzata  |
|          | da va_start, in questo momento sta puntando,        |
|          | specificandone anche il tipo. Ogni lettura fa       |
|          | avanzare il puntatore.                              |
|          |                                                     | 
| va_end   | Per indicare che non si eseguiranno piu' letture    |
|          | letture (va_arg) della lista, per poter nuovamente  |
|          | leggere la lista dopo una va_end, bisogna ripetere  |
|          | il va_start, che si posiziona nuovamente al primo   |
|          | elemento della lista anonima.                       |
|          |                                                     |
| va_copy  | (introdotta con C99) permette di copiare lo stato   |
|          | di una lista di argomenti, magari per posizionarsi  |
|          | in un punto precedente, per ripartire da li.        |
|                                                                |
| >> ESEMPIO :                                                   | 
|                                                                |
| #include "stdio.h"                                             |
| #include "stdarg.h"                                            |
|                                                                |
| int somma (int n, ...)                                         |
| {                                                              |
|     va_list args;                                              |
|     int risultato = 0;                                         |
|                                                                |
|     va_start(args, n);                                         |
|                                                                |
|     for (int i = 0; i < n; i++)                                |
|     {                                                          |
|          risultato += va_args(args, int);                      |
|     }                                                          |
|                                                                |
|     va_end(args);                                              |
|                                                                |
|     return risultato;                                          |
| }                                                              |
|                                                                |
| int main(void)                                                 |
| {                                                              |
|     printf ("%d\n", somma(3, 10, 20, 30));  // 60              |
|     printf ("%d\n", somma(2,  5,  7));      // 12              |
|     return 0;                                                  |
| }                                                              |
|                                                                |
| >> PARAMETRI MACRO : I nomi dei parametri utilizzati nelle 4   |
| macro, sono ininfluenti a chi le usa, ma normalmente si        |
| utilizzano questi nomi :                                       |
|                                                                | 
| ap       | normalmente conosciuto con questo nome.             |
| param    | parametro nominato che precede ... nella funzione.  |
| type     | descrive il tipo richiesto a va_arg.                |
| dest/src | chiariscono immediatamente la direzione di copia.   |
|                                                                |
'----------------------------------------------------------------' */

#ifndef  _STDARG_H
#define  _STDARG_H

typedef __builtin_va_list va_list;

#define va_start(ap, param)  __builtin_va_start(ap, param) 
#define va_arg(ap, type)     __builtin_va_arg(ap, type) 
#define va_end(ap)           __builtin_va_end(ap)           
#define va_copy(dest, src)   __builtin_va_copy(dest, src) 

#endif  
