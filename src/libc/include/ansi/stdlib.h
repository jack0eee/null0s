
/* stdlib.h di libc stardard [valido per C89/C90/C99] */

#ifndef STDLIB_H
#define STDLIB_H

/* -------- indipendenti dal sistema --------- */

int       abs     (int j);
long      labs    (long j);
long long llabs   (long long j);

/* --- */

typedef struct {
    int quot ;
    int rem ;
} div_t;

div_t     div     (int numer, int denom);

/* --- */

typedef struct {
    int quot ;
    int rem ;
} ldiv_t;

ldiv_t    ldiv    (long numer, long denom);

/* --- */

typedef struct {
    int quot ;
    int rem ;
} lldiv_t;

lldiv_t   lldiv   (long long numer, long long denom);

/* --- */

int       atoi    (const char *nptr);
long      atol    (const char *nptr);
long long atoll   (const char *nptr);   //-------------SONO QUI--------------

/* --- */

int       rand    (void);
void      srand   (unsigned int seed);

/* --- */ 

void      qsort   (void *base, size_t nmemb, size_t size,  
                   int (*compar)(const void *, const void *));

void     *bsearch (const void *key, const void *base, size_t nmemb, size_t size, 
                   int (*compar)(const void *, const void *));

// [...]

#endif

/* EOF */

