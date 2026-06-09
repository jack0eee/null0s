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
#                 '--- device_io.c
#                        \ 
#                        '--- io.c
#
#
#


#--- environment 

#--- Architettura : x86 
ARCH=x86

#-------------------
PATH_HOME=~/null0s
PATH_SOURCE=$PATH_HOME/src
PATH_SOURCE_BOOT=$PATH_SOURCE/boot
PATH_SOURCE_ARCH=$PATH_SOURCE/arch/$ARCH
PATH_SOURCE_LIBC=$PATH_SOURCE/libc
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
#| arch   |
#|        '-------------------------------------.
#| Su OpenBSD bisogna disabilitare :            |
#| * stack protector                            |
#| * PIE/PIC                                    |
#| altrimenti il kernel non linka correttamente |
#'----------------------------------------------'
echo "build $PATH_SOURCE_ARCH/io.c"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -c $PATH_SOURCE_ARCH/io.c \
   -o $PATH_SOURCE_ARCH/io.o

#.----------------.
#| driver -> BASE |
#|                '-----------------------------.
#| Su OpenBSD bisogna disabilitare :            |
#| * stack protector                            |
#| * PIE/PIC                                    |
#| altrimenti il kernel non linka correttamente |
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

#.---------------.
#| driver -> VGA |
#|               '------------------------------.
#| Su OpenBSD bisogna disabilitare :            |
#| * stack protector                            |
#| * PIE/PIC                                    |
#| altrimenti il kernel non linka correttamente |
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

#.--------.
#| libc.c |
#|        '-------------------------------------.
#| Su OpenBSD bisogna disabilitare :            |
#| * stack protector                            |
#| * PIE/PIC                                    |
#| altrimenti il kernel non linka correttamente |
#'----------------------------------------------'
echo "build $PATH_SOURCE_LIBC/libc.c"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
   -I $PATH_SOURCE_LIBC/include \
   -c $PATH_SOURCE_LIBC/libc.c \
   -o $PATH_SOURCE_LIBC/libc.o
 
#.---------.
#| kernel  |
#|         '---------------------------.
#|                                     |
#|                                     |
#'-------------------------------------'
echo "build $PATH_SOURCE_KERNEL/kernel.c"
cc -m32 \
   -ffreestanding \
   -fno-stack-protector \
   -fno-pic \
   -fno-pie \
   -I $PATH_SOURCE_LIBC/include \
   -I $PATH_SOURCE_KERNEL/drivers/video/vga \
   -I $PATH_SOURCE_KERNEL/include \
   -c $PATH_SOURCE_KERNEL/kernel.c \
   -o $PATH_SOURCE_KERNEL/kernel.o 

#.-------.
#| Link  |
#|       '--------------------------------------.
#|                                              |
#|                                              |
#'----------------------------------------------'
echo "build $PATH_SOURCE/null0s.bin <- boot/boot.o, arch/x86/io.o, kernel/drivers/base/device_io.o libc/libc.o kernel/kernel.o, kernel/drivers/video/vga/vga.o"

cc -m32 \
   -fPIC \
   -nostdlib \
   -Wl,-T,$PATH_SOURCE/linker.ld \
   -Wl,-z,notext \
   -o $PATH_SOURCE/null0s.bin \
         $PATH_SOURCE_BOOT/boot.o \
         $PATH_SOURCE_ARCH/io.o \
         $PATH_SOURCE_LIBC/libc.o \
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
