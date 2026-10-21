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

#--- Architettura : i386 
ARCH=i386

#-------------------
PATH_HOME=~/null0s
PATH_SOURCE=$PATH_HOME/src
PATH_SOURCE_BOOT=$PATH_SOURCE/boot
PATH_SOURCE_ARCH=$PATH_SOURCE/arch/$ARCH
PATH_SOURCE_LIBC=$PATH_SOURCE/libc
#---
PATH_SOURCE_APPL=$PATH_SOURCE/appl
#---
PATH_SOURCE_KERNEL=$PATH_SOURCE/kernel
PATH_BUILD=$PATH_HOME/build
#------------------------------

echo "build null0s"

#.--------.
#| boot.s | 
#|        '-------------------------------------.
#|                                              |
#|                                              |
#|                                              |
#|                                              |
#'----------------------------------------------'
echo "build $PATH_SOURCE_BOOT/boot.s"
cc -m32 \
   -c $PATH_SOURCE_BOOT/boot.s \
   -o $PATH_SOURCE_BOOT/boot.o

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
echo "build $PATH_SOURCE_ARCH/io.c"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -c $PATH_SOURCE_ARCH/io.c \
   -o $PATH_SOURCE_ARCH/io.o

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
echo "build $PATH_SOURCE_KERNEL/drivers/base/device_io.c"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -I $PATH_SOURCE_ARCH \
   -c $PATH_SOURCE_KERNEL/drivers/base/device_io.c \
   -o $PATH_SOURCE_KERNEL/drivers/base/device_io.o

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
echo "build $PATH_SOURCE_KERNEL/drivers/video/vga/lib/libvga.c"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -I $PATH_SOURCE_KERNEL/drivers/base \
   -c $PATH_SOURCE_KERNEL/drivers/video/vga/libvga.c \
   -o $PATH_SOURCE_KERNEL/drivers/video/vga/libvga.o


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
echo "build $PATH_SOURCE_LIBC/ansi/ctype.c -> ctype.o"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -c $PATH_SOURCE_LIBC/ansi/ctype.c \
   -o $PATH_SOURCE_LIBC/ansi/ctype.o

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
echo "build $PATH_SOURCE_LIBC/ansi/string.c -> string.o"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -c $PATH_SOURCE_LIBC/ansi/string.c \
   -o $PATH_SOURCE_LIBC/ansi/string.o

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
echo "build $PATH_SOURCE_LIBC/ansi/stdlib.c -> stdlib.o"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -c $PATH_SOURCE_LIBC/ansi/stdlib.c \
   -o $PATH_SOURCE_LIBC/ansi/stdlib.o

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
echo "build $PATH_SOURCE_LIBC/ansi/stdio.c -> stdio.o"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
   -I $PATH_SOURCE_LIBC/include/ansi/ \
   -c $PATH_SOURCE_LIBC/ansi/stdio.c \
   -o $PATH_SOURCE_LIBC/ansi/stdio.o

#.--------.
#| libc.c |
#|        '-------------------------------------.
#|                                              |
#| La lib.c complessiva, sostituita da          |
#| librerie separate.                           |
#|                                              |
#'----------------------------------------------'
#echo "build $PATH_SOURCE_LIBC/libc.c"
#cc -m32 \
#   -ffreestanding \
#   -fno-stack-protector \
#   -fno-pic \
#   -fno-pie \
#   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
#   -I $PATH_SOURCE_KERNEL/libk \
#   -I $PATH_SOURCE_LIBC/include/ansi \
#   -I $PATH_SOURCE_LIBC/include/posix \
#   -c $PATH_SOURCE_LIBC/libc.c \
#   -o $PATH_SOURCE_LIBC/libc.o

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
echo "build $PATH_SOURCE_APPL/gameOfLife/gameOfLife.c"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
   -I $PATH_SOURCE_LIBC/include/ansi \
   -c $PATH_SOURCE_APPL/gameOfLife/gameOfLife.c \
   -o $PATH_SOURCE_APPL/gameOfLife/gameOfLife.o

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
#echo "build $PATH_SOURCE_KERNEL/libk/libk.c"
#cc -m32 \
#   -ffreestanding \
#   -fno-stack-protector \
#   -fno-pic \
#   -fno-pie \
#   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
#   -I $PATH_SOURCE_KERNEL/libk \
#   -c $PATH_SOURCE_KERNEL/libk/libk.c \
#   -o $PATH_SOURCE_KERNEL/libk/libk.o
 
#.---------.
#| kernel  |
#|         '---------------------------.
#|                                     |
#| Il kernel, colui che si contrappone |
#| tra la libc e l'hardware.           |
#|                                     |
#'-------------------------------------'
echo "build $PATH_SOURCE_KERNEL/kernel.c"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -I $PATH_SOURCE_APPL/gameOfLife \
   -I $PATH_SOURCE_LIBC/include/ansi \
   -I $PATH_SOURCE_LIBC/include/posix \
   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
   -c $PATH_SOURCE_KERNEL/kernel.c \
   -o $PATH_SOURCE_KERNEL/kernel.o 

#.-------.
#| Link  |
#|       '--------------------------------------.
#|                                              |
#|                                              |
#'----------------------------------------------'
echo "build $PATH_SOURCE/null0s.bin <- " \
     "boot/boot.o, "\
     "arch/$ARCH/io.o, "\
     "kernel/drivers/base/device_io.o, "\
     "libc/libc.o, "\
     "appl/gameOfLife/gameOfLife.o, "\
     "kernel/kernel.o, "\
     "kernel/drivers/video/vga/vga.o"

#cc -m32 \
#   -fPIC \
#   -nostdlib \
#   -Wl,-T,$PATH_SOURCE/linker.ld \
#   -Wl,-z,notext \
#   -o $PATH_SOURCE/null0s.bin \
#         $PATH_SOURCE_BOOT/boot.o \
#         $PATH_SOURCE_ARCH/io.o \
#         $PATH_SOURCE_LIBC/libc.o \
#         $PATH_SOURCE_APPL/gameOfLife/gameOfLife.o \
#         $PATH_SOURCE_KERNEL/libk/libk.o \
#         $PATH_SOURCE_KERNEL/kernel.o \
#         $PATH_SOURCE_KERNEL/drivers/base/device_io.o \
#         $PATH_SOURCE_KERNEL/drivers/video/vga/libvga.o 

cc -m32 \
   -fPIC \
   -nostdlib \
   -Wl,-T,$PATH_SOURCE/linker.ld \
   -Wl,-z,notext \
   -o $PATH_SOURCE/null0s.bin \
         $PATH_SOURCE_BOOT/boot.o \
         $PATH_SOURCE_ARCH/io.o \
         $PATH_SOURCE_LIBC/ansi/ctype.o \
         $PATH_SOURCE_LIBC/ansi/string.o \
         $PATH_SOURCE_LIBC/ansi/stdlib.o \
         $PATH_SOURCE_LIBC/ansi/stdio.o \
         $PATH_SOURCE_APPL/gameOfLife/gameOfLife.o \
         $PATH_SOURCE_KERNEL/kernel.o \
         $PATH_SOURCE_KERNEL/drivers/base/device_io.o \
         $PATH_SOURCE_KERNEL/drivers/video/vga/libvga.o

#.-----------------.
#| Create ISO Tree | 
#|                 '-----------------------------------.
#|                                                     |
#|                                                     |
#'-----------------------------------------------------'
echo "Create ISOTree null0s.bin $PATH_BUILD/iso/boot/"
mkdir -p $PATH_BUILD/iso/boot/grub
cp $PATH_SOURCE/null0s.bin $PATH_BUILD/iso/boot/

echo "Create Grub Menu Label for null0s"
cp $PATH_SOURCE/grub.cfg $PATH_BUILD/iso/boot/grub/

echo "done"


# :::... EOF
