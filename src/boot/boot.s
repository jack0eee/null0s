;
;  boot.s ( sintassi Intel / NASM )
;
;
; 

.intel_syntax noprefix

.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .text
.global _start
.extern kmain

.code32

_start:

     cli 

     mov esp, offset stack_top

     call kmain

halt:

     hlt
     jmp halt


.section .bss
.align 16

stack_botton:
.skip 16384

stack_top:


