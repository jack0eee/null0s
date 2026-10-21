/*
.---------------------------------------------------------.
|                                                         |
|                                                         |
|                                                         |
|                                                         |
|                      LIBC / STDLIB                      |
|                                                         |
|                                                         |
|                                                         |
'---------------------------------------------------------' */

#include "stdlib.h"

/*
.--------------------------------------------------.
| abs   | Restituisce il valore assoluto di un     |
|         intero. Se negativo, moltiplica il       |
|         valore * -1. Se e' 0 o positivo invece   |
|         non fa nulla, restituisce il medesimo    |
|         valore ricevuto. Attenzione che il       |
|         corrispondnete positivo di INT_MIN e'    |
|         fuori dagli interi, quindi in quel caso  |
|         il comportamento secondo la specifica e' |
|         indefinito.                              |
'--------------------------------------------------' */
int abs (int j)
{
    // missing gestione INT_MIN (definite in limits.h)
    if ( j < 0 )
       return j * -1 ;

    return j ;
}

/*
.--------------------------------------------------.
| labs  | Restituisce il valore assoluto di un     |
|         intero long. Se negativo, moltiplica il  |
|         valore * -1. Se e' 0 o positivo invece   |
|         non fa nulla, restituisce il medesimo    |
|         valore ricevuto. Attenzione che il       |
|         corrispondnete positivo di LONG_MIN e'   |
|         fuori dagli interi long, quindi in quel  |
|         caso il comportamento secondo la         |
|         specifica e' indefinito.                 |
'--------------------------------------------------' */
long labs (long j)
{
    // missing gestione LONG_MIN (definite in limits.h)
    if ( j < 0 )
       return j * -1 ;

    return j ;
}

/*
.--------------------------------------------------.
| llabs | Restituisce il valore assoluto di un     |
|         intero longlong. Se negativo, moltiplica |
|         il valore * -1. Se e' 0 o positivo invece|
|         non fa nulla, restituisce il medesimo    |
|         valore ricevuto. Attenzione che il       |
|         corrispondnete positivo di LLONG_MIN e'  |
|         fuori dagli interi longlong, quindi in   |
|         quel caso il comportamento secondo la    |
|         specifica e' indefinito.                 |
'--------------------------------------------------' */
long long llabs (long long j)
{
    // missing gestione LLONG_MIN (definite in limits.h)
    if ( j < 0 )
       return j * -1 ;

    return j ;
}

/*
.--------------------------------------------------.
| div   | esegue la divisione tra 2 interi, e      |
|         restituisce il risultato nella struttura |
|         div_t.                                   |
'--------------------------------------------------' */
div_t div (int numer, int denom)
{
      div_t result ; 

      result.quot = numer / denom ;
      result.rem  = numer % denom ;

      return result ;
}

/*
.--------------------------------------------------.
| ldiv  | esegue la divisione tra 2 interi long, e |                                          
|         restituisce il risultato nella struttura |                                          
|         ldiv_t.                                  |
'--------------------------------------------------' */
ldiv_t ldiv (long numer, long denom)
{
      ldiv_t result ;

      result.quot = numer / denom ;
      result.rem  = numer % denom ;

      return result ;
}

/*
.--------------------------------------------------.
| lldiv | esegue la divisione tra 2 long long, e   |                                          
|         restituisce il risultato nella struttura |                                          
|         lldiv_t.                                 |
'--------------------------------------------------' */
lldiv_t lldiv (long long numer, long long denom)
{
      lldiv_t result ;

      //result.quot = numer / denom ;
      //result.rem  = numer % denom ;

      return result ;
};

/*
.--------------------------------------------------.
| atoi  |                                          |
|                                                  |
'--------------------------------------------------' */
int atoi (const char *nptr)
{
    return 0;
}; 

/*
.--------------------------------------------------.
| atol  |                                          |
|                                                  |
'--------------------------------------------------' */
long atol (const char *nptr)
{
    return 0;
};

/*
.--------------------------------------------------.
| atoll |                                          |
|                                                  |
'--------------------------------------------------' */
long long atoll (const char *nptr)
{
    return 0;
};

/*
.--------------------------------------------------.
| qsort |                                          |
|                                                  |
'--------------------------------------------------' */
void qsort (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
};

/*
.--------------------------------------------------.
| bsearch |                                        |
|                                                  |
'--------------------------------------------------' */
//void *bsearch (const void *key,const void *base,size_t nmemb,size_t size,int (*compar)(const void *,const void *))
//{
//};


/* =============== STDLIB | ANSI ================= */

