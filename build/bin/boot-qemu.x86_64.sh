#!/bin/sh

#--- Architettura : x86_64 
ARCH=x86_64 

#--- environment 
PATH_HOME=~/null0s
PATH_SOURCE=$PATH_HOME/src
PATH_SOURCE_BOOT=$PATH_SOURCE/boot
PATH_SOURCE_LIBC=$PATH_SOURCE/libc
PATH_SOURCE_KERNEL=$PATH_SOURCE/kernel
PATH_BUILD=$PATH_HOME/build
#------------------------------

echo "boot $PATH_BUILD/iso/boot/null0s.$ARCH.bin"

#.--------.
#| boot.s |
#'--------'
qemu-system-x86_64 \
  -kernel $PATH_BUILD/iso/boot/null0s.$ARCH.bin \
  -boot order=c \
  -no-reboot \
  -serial none \
  -net none

exit 0
 
