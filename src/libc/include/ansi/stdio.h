
/* stdio.h di libc stardard -- C ANSI  */

#ifndef STDIO_H
#define STDIO_H

#include "stddef.h" //?????????????????
#include "stdarg.h" //?????????????????

#include "libvga.h" 

/* Struttura FILE - Mantenere lo stato di uno stream | Dichiarazione didattica */

typedef struct FILE {
      int            fd       ;
      unsigned char *buffer   ;
      size_t         buf_size ;
      size_t         pos      ;
      size_t         count    ;
      int            flags    ;
      int            eof      ;
      int            error    ;
} FILE ;


/* Struttura per gestione posizione file (fgetpos e fsetpos) */

typedef long fpos_t ;


 
/*
.-------------.
| File Access |
'-------------' */ 
FILE *fopen     ( const char *restrict filename, const char *restrict mode );                        // NO
FILE *freopen   ( const char *restrict filename, const char *restrict mode, FILE *restrict stream ); // NO
int   fclose    ( FILE *stream );                                                                    // NO
int   fflush    ( FILE *stream );                                                                    // NO

/*
.------------------------.
| Character input/output |
'------------------------' */
int   fgetc     ( FILE *stream );                                                                    // NO
char *fgets     ( char *restrict s, int n, FILE *restrict stream );                                  // NO

int   fputc     ( int c, FILE *stream );                                                             // NO
int   fputs     ( const char *restrict s, FILE *restrict stream );                                   // NO

int   getc      ( FILE *stream);                                                                     // NO
int   getchar   ( void);                                                                             // NO 
char *gets      ( char *s);                                                                          // NO 
 
int   putc      ( int c, FILE *stream);                                                              // NO
int   putchar   ( int c );                                                                           // SI
int   puts      ( const char *str ) ;                                                                // SI

int   ungetc    ( int c, FILE *stream ) ;                                                            // NO 

/* 
.------------------------.
| Formatted input/output |
'------------------------' */
int   fprintf   ( FILE *restrict stream, const char *restrict format, ... );                         // NO
int   fscanf    ( FILE *restrict stream, const char *restrict format, ... );                         // NO
int   printf    ( const char *restrict format, ... );                                                // NO
int   scanf     ( const char *restrict format, ... );                                                // NO
int   snprintf  ( char *restrict s, size_t n, const char *restrict format, ... );                    // NO
int   sprintf   ( char *restrict s, const char *restrict format, ... );                              // NO
int   vfprintf  ( FILE *restrict stream, const char *restrict format, va_list arg );                 // NO
int   vfscanf   ( FILE *restrict stream, const char *restrict format, va_list arg );                 // NO
int   vprintf   ( const char *restrict format, va_list arg );                                        // NO
int   vscanf    ( const char *restrict format, va_list arg );                                        // NO
int   vsnprintf ( char *restrict s, size_t n, const char *restrict format, va_list arg );            // NO
int   vsprintf  ( char *restrict s, const char *restrict format, va_list arg );                      // NO

/*
.---------------------.
| Direct input/output | 
'---------------------' */
size_t fread   ( void *restrict ptr, size_t size, size_t nmemb, FILE *restrict stream );            // NO
size_t fwrite  ( const void *restrict ptr, size_t size, size_t nmemb, FILE *restrict stream );      // NO

/*
.------------------.
| File Positioning |
'------------------' */
int   fgetpos  ( FILE *restrict stream, fpos_t *restrict pos );                                     // NO
int   fseek    ( FILE *stream, long offset, int whence );                                           // NO
int   fsetpos  ( FILE *stream, const fpos_t *pos );                                                 // NO
long  ftell    ( FILE *stream );                                                                    // NO
void  rewind   ( FILE *stream );                                                                    // NO

/*
.----------------.
| Error Handling |
'----------------' */
void  clearerr ( FILE *stream );                                                                   // NO
int   feof     ( FILE *stream );                                                                   // NO
int   ferror   ( FILE *stream );                                                                   // NO
int   perror   ( FILE *stream );                                                                   // NO

/* 
.-----------------.
| File Operations |
'-----------------' */
int   remove   ( const char *filename );                                                           // NO
int   rename   ( const char *oldname, const char *newname );                                       // NO
FILE  tmpfile  ( void );                                                                           // NO
char *tmpnam   ( char *s );                                                                        // NO

/*
.-------------------.
| Buffer Management |
'-------------------' */
int   setbuf   ( FILE *restrict stream, char *restrict buf );                                     // NO
int   setvbuf  ( FILE *restrict stream, char *restrict buf, int mode, size_t size );              // NO


#endif

// Avanzamento : funzioni [44] - Implementate [2] - Da Implementare [42]

/* EOF */


