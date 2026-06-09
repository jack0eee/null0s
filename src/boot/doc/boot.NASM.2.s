/* sintassi Intel / NASM|YAST 

/* boot.asm */

;per usare GCC clang con sintassi NASM, aggiungere
.intel_syntax noprefix  

BITS 32

.section .multiboot
.align 4

MAGIC     equ 0x1BADB002
FLAGS     equ 0x00000003
CHECKSUM  equ -(MAGIC + FLAGS)

dd MAGIC
dd FLAGS
dd CHECKSUM

.section .text
.global _start
.extern kmain

_start:

     cli 

     mov esp, stack_top

     call kmain

.hang:

     hlt
     jmp .hang


section .bss
align 16

stack_botton:
    resb 16384

stack_top:


