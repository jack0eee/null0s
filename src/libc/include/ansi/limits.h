
/* ----------------- limits.h ------------------- */

#ifndef LIMITS_H
#define LIMITS_H

/* limiti dei tipi char */

#define CHAR_BIT    8
#define SCHAR_MIN (-128)
#define SCHAR_MAX   127
#define UCHAR_MAX   255


/* limiti di char : dipende dall'implementazione */

#define CHAR_MIN    SCHAR_MIN
#define CHAR_MAX    SCHAR_MAX


/* limiti di short */

#define SHRT_MIN  (-32768)
#define SHRT_MAX    32767
#define USHRT_MAX   65535U


/* limiti di int */

#define INT_MIN   (-2147483647 - 1)
#define INT_MAX     2147483647
#define UINT_MAX    4294967295U


/* limiti di long */

#define LONG_MIN  (-2147483647 - 1L)
#define LONG_MAX    2147483647
#define ULONG_MAX   4294967295U


/* limiti di long long */

#define LLONG_MIN (-9223372036854775807LL - 1LL)
#define LLONG_MAX   9223372036854775807LL 
#define SLLONG_MAX  18446744073709551615ULL

#endif

 

 
