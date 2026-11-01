OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)

SECTIONS
{
    . = 1M;

    /* Multiboot header: dati */

    .multiboot ALIGN(4) :
    {
        KEEP(*(.multiboot))
    }

    /* Codice eseguibile */

    .text ALIGN(4K) :
    {
        *(.text)
        *(.text.*)
    }

    /* Dati in sola lettura */

    .rodata ALIGN(4K) :
    {
        *(.rodata)
        *(.rodata.*)
    }

    /* Dati inizializzati */

    .data ALIGN(4K) :
    {
        *(.data)
        *(.data.*)
    }

    /* Dati non inizializzati */

    .bss ALIGN(4K) :
    {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    }
}

