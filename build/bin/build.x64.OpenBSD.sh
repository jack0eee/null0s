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

#--- Architettura : x64 
ARCH=x64

#-------------------
PATH_HOME=~/null0s
PATH_SOURCE=$PATH_HOME/src
PATH_SOURCE_BOOT=$PATH_SOURCE/boot/arch/$ARCH
PATH_SOURCE_ARCH=$PATH_SOURCE/arch/$ARCH
PATH_SOURCE_LIBC=$PATH_SOURCE/libc
#---
PATH_SOURCE_APPL=$PATH_SOURCE/appl
#---
PATH_SOURCE_KERNEL=$PATH_SOURCE/kernel
PATH_BUILD=$PATH_HOME/build
#------------------------------

case "$ARCH" in 

   i386) 
         opz="-m32"
         ;;

   x64)  
         opz="-m64"
         ;;

   *)    
         echo "error : architettura non supporta" 
         exit 0
         ;;
esac

echo "build null0s ($ARCH|$opz) ..."

#.--------.
#| clean  |
#|        '-------------------------------------.
#|                                              |
#|                                              |
#|                                              |
#|                                              |
#'----------------------------------------------'
echo "clean $PATH_SOURCE (*.$ARCH.o)"
find $PATH_SOURCE -name *.$ARCH.o -exec rm {} + 

#.--------.
#| boot.s | 
#|        '-------------------------------------.
#|                                              |
#|                                              |
#|                                              |
#|                                              |
#'----------------------------------------------'
echo "build $PATH_SOURCE_BOOT/boot.$ARCH.s -> boot.$ARCH.o"
cc $opz \
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
echo "build $PATH_SOURCE_ARCH/io.c -> io.$ARCH.o"
cc $opz \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -c $PATH_SOURCE_ARCH/io.c \
   -o $PATH_SOURCE_ARCH/io.$ARCH.o

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
echo "build $PATH_SOURCE_KERNEL/drivers/base/device_io.c -> device_io.$ARCH.o"
cc $opz \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -I $PATH_SOURCE_ARCH \
   -c $PATH_SOURCE_KERNEL/drivers/base/device_io.c \
   -o $PATH_SOURCE_KERNEL/drivers/base/device_io.$ARCH.o

#.-----------------------.
#| driver -> video/vga.o |
#|                       '----------------------.
#|                                              |
#| Implementa il driver VGA, ossia una          |
#| collezione di funzioni                       |
#|                                              |
#| Dipendenze : device_io.o                     |
#|                                              | 
#'----------------------------------------------'
echo "build $PATH_SOURCE_KERNEL/drivers/video/vga/lib/libvga.c -> libvga.$ARCH.o"
cc $opz \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
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
echo "build $PATH_SOURCE_LIBC/ansi/ctype.c -> ctype.$ARCH.o"
cc $opz \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
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
echo "build $PATH_SOURCE_LIBC/ansi/string.c -> string.$ARCH.o"
cc $opz \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
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
echo "build $PATH_SOURCE_LIBC/ansi/stdlib.c -> stdlib.$ARCH.o"
cc $opz \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
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
echo "build $PATH_SOURCE_LIBC/ansi/stdio.c -> stdio.$ARCH.o"
cc $opz \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
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
#echo "build $PATH_SOURCE_LIBC/libc.c -> libc.$ARCH.o"
#cc $opz \
#   -ffreestanding \
#   -fno-stack-protector \
#   -fno-pic \
#   -fno-pie \
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
echo "build $PATH_SOURCE_APPL/gameOfLife/gameOfLife.c -> gameOfLife.$ARCH.o"
cc $opz \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
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
echo "build $PATH_SOURCE_APPL/printIntSizeof/printIntSizeof.c -> printIntSizeof.$ARCH.o"
cc $opz \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
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
#echo "build $PATH_SOURCE_KERNEL/libk/libk.c -> libk.$ARCH.o"
#cc $opz \
#   -ffreestanding \
#   -fno-stack-protector \
#   -fno-pic \
#   -fno-pie \
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
echo "build $PATH_SOURCE_KERNEL/kernel.c -> kernel.$ARCH.o"
cc $opz \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
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
echo "build $PATH_SOURCE/null0s.$ARCH.bin <- " \
     "boot/arch/$ARCH/boot.$ARCH.o, "\
     "arch/$ARCH/io.$ARCH.o, "\
     "kernel/drivers/base/device_io.$ARCH.o, "\
     "libc/libc.$ARCH.o, "\
     "appl/gameOfLife/gameOfLife.$ARCH.o, "\
     "kernel/kernel.$ARCH.o, "\
     "kernel/drivers/video/vga/vga.$ARCH.o -> null0s.$ARCH.bin"

#cc $opz \
#   -fPIC \
#   -nostdlib \
#   -Wl,-T,$PATH_SOURCE_KERNEL/linker.$ARCH.ld \
#   -Wl,-z,notext \
#   -o $PATH_SOURCE_KERNEL/null0s.$ARCH.bin \
#      $PATH_SOURCE_BOOT/boot.$ARCH.o \
#      $PATH_SOURCE_ARCH/io.$ARCH.o \
#      $PATH_SOURCE_LIBC/libc.$ARCH.o \
#      $PATH_SOURCE_APPL/gameOfLife/gameOfLife.$ARCH.o \
#      $PATH_SOURCE_KERNEL/libk/libk.$ARCH.o \
#      $PATH_SOURCE_KERNEL/kernel.$ARCH.o \
#      $PATH_SOURCE_KERNEL/drivers/base/device_io.$ARCH.o \
#      $PATH_SOURCE_KERNEL/drivers/video/vga/libvga.$ARCH.o 

cc $opz \
   -no-pie \
   -nostdlib \
   -Wl,-T,$PATH_SOURCE_KERNEL/linker.$ARCH.ld \
   -Wl,-z,notext \
   -o $PATH_SOURCE_KERNEL/null0s.$ARCH.bin \
      $PATH_SOURCE_BOOT/boot.$ARCH.o \
      $PATH_SOURCE_ARCH/io.$ARCH.o \
      $PATH_SOURCE_LIBC/ansi/ctype.$ARCH.o \
      $PATH_SOURCE_LIBC/ansi/string.$ARCH.o \
      $PATH_SOURCE_LIBC/ansi/stdlib.$ARCH.o \
      $PATH_SOURCE_LIBC/ansi/stdio.$ARCH.o \
      $PATH_SOURCE_APPL/gameOfLife/gameOfLife.$ARCH.o \
      $PATH_SOURCE_APPL/printIntSizeof/printIntSizeof.$ARCH.o \
      $PATH_SOURCE_KERNEL/kernel.$ARCH.o \
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
cp $PATH_SOURCE_KERNEL/null0s.$ARCH.bin $PATH_BUILD/iso/boot/

echo "Create Grub Menu Label for null0s"
cp $PATH_SOURCE/boot/grub.cfg $PATH_BUILD/iso/boot/grub/

echo "done"


# :::... EOF
