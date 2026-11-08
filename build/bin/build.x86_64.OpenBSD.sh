#!/bin/sh

#
#  kernel 
#    \
#    '--- boot.s 
#    |
#    '--- libc.c  
#           \
#           '--- vga.c 
#                 \
#                 '--- <ARCH>                   X 
#                        \                      |
#                        '--- device_io.c       |  strato hardware
#                                \              |
#                                '--- io.c      X 
#
#
#

#--- ENVIRONMENT

#--- Architettura : x86_64 
ARCH=x86_64
CC=clang 

#-------------------
PATH_HOME=~/null0s
PATH_SOURCE=$PATH_HOME/src
#---
PATH_SOURCE_BOOT=$PATH_SOURCE/boot/arch/$ARCH
PATH_SOURCE_LIBC=$PATH_SOURCE/libc
PATH_SOURCE_APPL=$PATH_SOURCE/appl
PATH_SOURCE_KERNEL=$PATH_SOURCE/kernel
#---
PATH_BUILD=$PATH_HOME/build
#------------------------------

case "$ARCH" in 

   i386) 
         AFLAGS="-m32 -target i386-unknown-elf"
         CFLAGS="-m32 -target i386-unknown-elf -ffreestanding -fno-stack-protector -fno-pic -fno-pie -fno-builtin" 
         ;;

   x86_64)  
         AFLAGS="-m64"
         CFLAGS="-m64 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -fno-builtin" 
         ;;

   *)    
         echo "error : architettura non supporta" 
         exit 0
         ;;
esac

echo "build null0s ($ARCH|$CFLAGS)"

#.--------.
#| clean  |
#|        '-------------------------------------.
#|                                              |
#|                                              |
#|                                              |
#|                                              |
#'----------------------------------------------'
echo "clean $PATH_SOURCE (*.$ARCH.o)"
find $PATH_SOURCE -name "*.$ARCH.o" -exec rm {} + 

#.--------.
#| boot.s | 
#|        '-------------------------------------.
#|                                              |
#|                                              |
#|                                              |
#|                                              |
#'----------------------------------------------'
echo "$CC $PATH_SOURCE_BOOT/boot.$ARCH.s -> boot.$ARCH.o"
$CC $AFLAGS \
   -c $PATH_SOURCE_BOOT/boot.$ARCH.s \
   -o $PATH_SOURCE_BOOT/boot.$ARCH.o

#.--------.
#| io.o   |
#|        '-------------------------------------.
#|                                              |
#| Lo strato piu' basso.                        |
#| Implementa funzionalita' utilizzate dai      |
#| drivers di periferica.                       |
#|                                              |
#| Dipendenze : nessuna.                        |
#|                                              |
#'----------------------------------------------'
echo "$CC $PATH_SOURCE_KERNEL/drivers/base/io.c -> io.$ARCH.o"
$CC $CFLAGS \
   -c $PATH_SOURCE_KERNEL/drivers/base/io.c \
   -o $PATH_SOURCE_KERNEL/drivers/base/io.$ARCH.o

#.-----------------------.
#| driver -> device_io.o |
#|                       '----------------------.
#|                                              |
#| Libreria di base dei driver. Si occupano     |
#| anche all'hardware tramite la libreria io.   |
#|                                              |
#| Dipendenze : io.o                            |
#|                                              |
#'----------------------------------------------'
echo "$CC $PATH_SOURCE_KERNEL/drivers/base/device_io.c -> device_io.$ARCH.o"
$CC $CFLAGS \
   -c $PATH_SOURCE_KERNEL/drivers/base/device_io.c \
   -o $PATH_SOURCE_KERNEL/drivers/base/device_io.$ARCH.o

#.--------------------------.
#| driver -> video/libvga.o |
#|                          '-------------------.
#|                                              |
#| Implementa il driver VGA, ossia una          |
#| collezione di funzioni                       |
#|                                              |
#| Dipendenze : device_io.o                     |
#|                                              | 
#'----------------------------------------------'
echo "$CC $PATH_SOURCE_KERNEL/drivers/video/vga/lib/libvga.c -> libvga.$ARCH.o"
$CC $CFLAGS \
   -I $PATH_SOURCE_KERNEL/drivers/base \
   -c $PATH_SOURCE_KERNEL/drivers/video/vga/libvga.c \
   -o $PATH_SOURCE_KERNEL/drivers/video/vga/libvga.$ARCH.o


#.-------------------.
#| libc/ansi/ctype.c |
#|                   '--------------------------.
#|                                              |
#| Libreria LIBC che implementa funzioni        |
#| per verificare il tipo di un valore o se e'  |
#| all'interno di un certo range.               |
#|                                              |
#| Dipendenze : nessuna.                        |
#|                                              |
#'----------------------------------------------'
echo "$CC $PATH_SOURCE_LIBC/ansi/ctype.c -> ctype.$ARCH.o"
$CC $CFLAGS \
   -c $PATH_SOURCE_LIBC/ansi/ctype.c \
   -o $PATH_SOURCE_LIBC/ansi/ctype.$ARCH.o

#.--------------------.
#| libc/ansi/string.c |
#|                    '-------------------------.
#|                                              |
#| Libreria LIBC che implementa funzioni        |
#| per manipolare le stringhe : copia,          |
#| inizializzazione, confronti, etc             |
#|                                              |
#| Dipendenze : nessuna.                        |
#|                                              |
#'----------------------------------------------'
echo "$CC $PATH_SOURCE_LIBC/ansi/string.c -> string.$ARCH.o"
$CC $CFLAGS \
   -c $PATH_SOURCE_LIBC/ansi/string.c \
   -o $PATH_SOURCE_LIBC/ansi/string.$ARCH.o

#.--------------------.
#| libc/ansi/stdlib.c |
#|                    '-------------------------.
#|                                              |
#| Libreria LIBC che implementa funzioni        |
#| non tematiche ma generiche di base, quali    |
#| di conversione, valore assoluto ed altre.    |
#|                                              |
#| Dipendenze : nessuna.                        |
#|                                              |
#'----------------------------------------------'
echo "$CC $PATH_SOURCE_LIBC/ansi/stdlib.c -> stdlib.$ARCH.o"
$CC $CFLAGS \
   -c $PATH_SOURCE_LIBC/ansi/stdlib.c \
   -o $PATH_SOURCE_LIBC/ansi/stdlib.$ARCH.o

#.-------------------.
#| libc/ansi/stdio.c |
#|                   '--------------------------.
#|                                              |
#| Libreria LIBC che implementa funzioni di I/O |
#| Tramite queste funzioni e' possibile         |
#| scrivere un carattere a video, oppure        |
#| leggere il tasto premuto sulla tastiera.     |
#|                                              |
#| Dipendenze : driver (barmetal) *             |
#|              kernel (SO multiutente)         |
#|                                              |
#'----------------------------------------------'
echo "$CC $PATH_SOURCE_LIBC/ansi/stdio.c -> stdio.$ARCH.o"
$CC $CFLAGS \
   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
   -I $PATH_SOURCE_LIBC/include/ansi/ \
   -c $PATH_SOURCE_LIBC/ansi/stdio.c \
   -o $PATH_SOURCE_LIBC/ansi/stdio.$ARCH.o

#.--------.
#| libc.c |
#|        '-------------------------------------.
#|                                              |
#| La lib.c complessiva, sostituita da          |
#| librerie separate.                           |
#|                                              |
#'----------------------------------------------'
#echo "$CC $PATH_SOURCE_LIBC/libc.c -> libc.$ARCH.o"
#$CC $CFLAGS \
#   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
#   -I $PATH_SOURCE_KERNEL/libk \
#   -I $PATH_SOURCE_LIBC/include/ansi \
#   -I $PATH_SOURCE_LIBC/include/posix \
#   -c $PATH_SOURCE_LIBC/libc.c \
#   -o $PATH_SOURCE_LIBC/libc.$ARCH.o

#.---------------------.
#| APPLFake/GameOfLife |
#|                     '------------------------.
#|                                              |
#| Applicazione Fake per verificare alcune      |
#| funzioni dal kernel (barmetal) del driver    |
#| VGA, in particolare la putchar(c), ossia la  |
#| visualizzazione di un carattere a video.     | 
#|                                              |
#| Dipendenze : kernel/drivers/video/vga e      |
#|              libc/ansi                       |
#|                                              |
#'----------------------------------------------'
echo "$CC $PATH_SOURCE_APPL/gameOfLife/gameOfLife.c -> gameOfLife.$ARCH.o"
$CC $CFLAGS \
   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
   -I $PATH_SOURCE_LIBC/include/ansi \
   -c $PATH_SOURCE_APPL/gameOfLife/gameOfLife.c \
   -o $PATH_SOURCE_APPL/gameOfLife/gameOfLife.$ARCH.o

#.-------------------------.
#| APPLFake/printIntSizeof |
#|                         '--------------------.
#|                                              |
#| Applicazione Fake per verificare alcune      |
#| funzioni dal kernel (barmetal) di libc       |
#| In particolare della stdio|printf e della    |
#| portatilita' di stdint.h                     |
#|                                              |
#| Dipendenze : libc/ansi                       |
#|                                              |
#'----------------------------------------------'
echo "$CC $PATH_SOURCE_APPL/printIntSizeof/printIntSizeof.c -> printIntSizeof.$ARCH.o"
$CC $CFLAGS \
   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
   -I $PATH_SOURCE_LIBC/include/ansi \
   -c $PATH_SOURCE_APPL/printIntSizeof/printIntSizeof.c \
   -o $PATH_SOURCE_APPL/printIntSizeof/printIntSizeof.$ARCH.o

#.---------------.
#| kernel/libk.c |
#|               '------------------------------.
#|                                              |
#| Libreria del kernel che serve per far        |
#| comunicare la libC con l'hardware tramite    |
#| per l'appunto il kernel e trasformare il SO  |
#| da "baremetal" a "multiutente". Esclusa      |
#| perche' ancora in fase di sviluppo.          |
#|                                              |
#'----------------------------------------------'
#echo "$CC $PATH_SOURCE_KERNEL/libk/libk.c -> libk.$ARCH.o"
#$CC $CFLAGS \
#   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
#   -I $PATH_SOURCE_KERNEL/libk \
#   -c $PATH_SOURCE_KERNEL/libk/libk.c \
#   -o $PATH_SOURCE_KERNEL/libk/libk.$ARCH.o
 
#.---------.
#| kernel  |
#|         '---------------------------.
#|                                     |
#| Il kernel, colui che si contrappone |
#| tra la libc e l'hardware.           |
#|                                     |
#'-------------------------------------'
echo "$CC $PATH_SOURCE_KERNEL/kernel.c -> kernel.$ARCH.o"
$CC $CFLAGS \
   -I $PATH_SOURCE_APPL/gameOfLife \
   -I $PATH_SOURCE_APPL/printIntSizeof \
   -I $PATH_SOURCE_LIBC/include/ansi \
   -I $PATH_SOURCE_LIBC/include/posix \
   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
   -c $PATH_SOURCE_KERNEL/kernel.c \
   -o $PATH_SOURCE_KERNEL/kernel.$ARCH.o 

#.-------.
#| Link  |
#|       '--------------------------------------.
#|                                              |
#|                                              |
#'----------------------------------------------'
echo "link $PATH_SOURCE/null0s.$ARCH.bin <- "\
     "boot/arch/$ARCH/boot.$ARCH.o,"\
     "libc/libc.$ARCH.o,"\
     "appl/gameOfLife/gameOfLife.$ARCH.o,"\
     "appl/printIntSizeof/printIntSizeof.$ARCH.o,"\
     "kernel/kernel.$ARCH.o,"\
     "kernel/drivers/base/io.$ARCH.o,"\
     "kernel/drivers/base/device_io.$ARCH.o,"\
     "kernel/drivers/video/vga/libvga.$ARCH.o"

#$CC $opz \
#   -fPIC \
#   -nostdlib \
#   -Wl,-T,$PATH_SOURCE_KERNEL/linker.$ARCH.ld \
#   -Wl,-z,notext \
#   -o $PATH_SOURCE_KERNEL/null0s.$ARCH.bin \
#      $PATH_SOURCE_BOOT/boot.$ARCH.o \
#      $PATH_SOURCE_LIBC/libc.$ARCH.o \
#      $PATH_SOURCE_APPL/gameOfLife/gameOfLife.$ARCH.o \
#      $PATH_SOURCE_APPL/printIntSizeof/printIntSizeof.$ARCH.o \
#      $PATH_SOURCE_KERNEL/libk/libk.$ARCH.o \
#      $PATH_SOURCE_KERNEL/kernel.$ARCH.o \
#      $PATH_SOURCE_KERNEL/drivers/base/io.$ARCH.o 
#      $PATH_SOURCE_KERNEL/drivers/base/device_io.$ARCH.o \
#      $PATH_SOURCE_KERNEL/drivers/video/vga/libvga.$ARCH.o 

$CC $opz \
   -no-pie \
   -nostdlib \
   -Wl,-T,$PATH_SOURCE_KERNEL/linker.$ARCH.ld \
   -Wl,-z,notext \
   -o $PATH_SOURCE_KERNEL/null0s.$ARCH.bin \
      $PATH_SOURCE_BOOT/boot.$ARCH.o \
      $PATH_SOURCE_LIBC/ansi/ctype.$ARCH.o \
      $PATH_SOURCE_LIBC/ansi/string.$ARCH.o \
      $PATH_SOURCE_LIBC/ansi/stdlib.$ARCH.o \
      $PATH_SOURCE_LIBC/ansi/stdio.$ARCH.o \
      $PATH_SOURCE_APPL/gameOfLife/gameOfLife.$ARCH.o \
      $PATH_SOURCE_APPL/printIntSizeof/printIntSizeof.$ARCH.o \
      $PATH_SOURCE_KERNEL/kernel.$ARCH.o \
      $PATH_SOURCE_KERNEL/drivers/base/io.$ARCH.o \
      $PATH_SOURCE_KERNEL/drivers/base/device_io.$ARCH.o \
      $PATH_SOURCE_KERNEL/drivers/video/vga/libvga.$ARCH.o

#.-----------------.
#| Create ISO Tree | 
#|                 '-----------------------------------.
#|                                                     |
#|                                                     |
#'-----------------------------------------------------'
echo "Create ISOTree $PATH_SOURCE_KERNEL/null0s.$ARCH.bin -> $PATH_BUILD/iso/boot/"
mkdir -p $PATH_BUILD/iso/boot/grub
mv $PATH_SOURCE_KERNEL/null0s.$ARCH.bin $PATH_BUILD/iso/boot/

echo "Create Grub Menu Label for null0s"
cp $PATH_SOURCE/boot/grub.cfg $PATH_BUILD/iso/boot/grub/

echo "done"


# :::... EOF
