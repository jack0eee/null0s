#include <stdio.h>  
#include <stdint.h> 

int printIntSizeof()
{

   // Tipi Interi Base (con segno)
   char               dChar             ;
   short    int       dShortInt         ;
   int                dInt              ;
   long               dLong             ;
   long long          dLongLong         ;
  
   // Tipi Intero Base (senza segno) 
   unsigned char      dCharUnsigned     ;  
   unsigned short int dShortIntUnsigned ;
   unsigned int       dIntUnsigned      ;
   unsigned long      dLongUnsigned     ;
   unsigned long long dLongLongUnsigned ;
 
   // Tipi Interi Portatili/stdint.h (con segno) 
   uint8_t  d8u  ;
   uint16_t d16u ;
   uint32_t d32u ;
   uint64_t d64u ;

   // Tipi Interi Portatili/stdint.h (senza segno)
   int8_t   d8   ;
   int16_t  d16  ;
   int32_t  d32  ;
   int64_t  d64  ;

   printf("\n");
   printf("---------------------------------\n"); 
   printf("stdint.h exploration!\n");
   printf("(mostra byte allocati)\n");
   printf("---------------------------------\n");

   printf("\n\n");
   printf(".---------------------------------------------.\n");
   printf("| CC | Tipo interi base                       |\n");
   printf("'---------------------------------------------'\n");
   printf("char     [%d]  |  uchar     [%d]\n", sizeof(dChar)     , sizeof(dCharUnsigned)    ) ;
   printf("short    [%d]  |  ushort    [%d]\n", sizeof(dShortInt) , sizeof(dShortIntUnsigned)) ;
   printf("int      [%d]  |  uint      [%d]\n", sizeof(dInt)      , sizeof(dIntUnsigned)     ) ;
   printf("long     [%d]  |  ulong     [%d]\n", sizeof(dLong)     , sizeof(dLongUnsigned)    ) ;
   printf("longlong [%d]  |  ulonglong [%d]\n", sizeof(dLongLong) , sizeof(dLongLongUnsigned)) ;

   printf("\n\n"); 
   printf(".---------------------------------------------.\n");
   printf("| stdint | tipo definiti                      |\n");
   printf("'---------------------------------------------'\n");   
   printf("int8_t   [%d]  |  uint8_t   [%d]\n", sizeof(d8)  , sizeof(d8u) ) ;
   printf("int16_t  [%d]  |  uint16_t  [%d]\n", sizeof(d16) , sizeof(d16u)) ;
   printf("int32_t  [%d]  |  uint32_t  [%d]\n", sizeof(d32) , sizeof(d32u)) ;
   printf("int64_t  [%d]  |  uint64_t  [%d]\n", sizeof(d64) , sizeof(d64u)) ;

   return 0;
}

