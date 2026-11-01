
/*
 * ============================================================
 * boot.s
 *
 * x86-64 Microkernel Bootstrap
 * GRUB - Multiboot 1
 *
 * GNU Assembler (GAS)
 * Intel Syntax
 *
 * Initial CPU mode : Protected Mode (32 bit)
 * Final CPU mode   : Long Mode (64 bit)
 *
 * ============================================================
 */

.intel_syntax noprefix


/* ============================================================
 * MULTIBOOT 1 HEADER
 * ============================================================
 */

.set ALIGN,       1 << 0
.set MEMINFO,     1 << 1
.set FLAGS,       ALIGN | MEMINFO

.set MAGIC,       0x1BADB002
.set CHECKSUM,    -(MAGIC + FLAGS)


.section .multiboot,"a"
.align 4

.long MAGIC
.long FLAGS
.long CHECKSUM


/* ============================================================
 * BOOTSTRAP - 32 BIT
 * ============================================================
 */

.section .text
.code32

.global _start
.extern kmain

_start:

    /*
     * Disable interrupts
     */

    cli
    cld

    /*
     * Save Multiboot parameters
     *
     * EAX = 0x2BADB002
     * EBX = Multiboot information structure
     */

    mov dword ptr [boot_magic], eax
    mov dword ptr [mbi_ptr], ebx

    /*
     * Initialize temporary stack
     */

    mov esp, offset stack_top

    /*
     * Check Multiboot magic
     */

    cmp eax, 0x2BADB002
    jne boot_error


/* ============================================================
 * CHECK CPU FEATURES
 * ============================================================
 */

check_cpu:

    /*
     * Check CPUID availability
     */

    pushfd
    pop eax

    mov ecx, eax
    xor eax, 0x00200000

    push eax
    popfd

    pushfd
    pop eax

    push ecx
    popfd

    xor eax, ecx
    test eax, 0x00200000

    jz boot_error

    /*
     * Check PAE and Long Mode support
     */

    mov eax, 1
    cpuid

    test edx, 1 << 6
    jz boot_error

    mov eax, 0x80000000
    cpuid

    cmp eax, 0x80000001
    jb boot_error

    mov eax, 0x80000001
    cpuid

    test edx, 1 << 29
    jz boot_error


/* ============================================================
 * INITIALIZE PAGE TABLES
 *
 * PML4 -> PDPT -> PD
 *
 * Identity mapping:
 * 0x00000000 - 0x3FFFFFFF
 *
 * Page size: 2 MiB
 * Total: 1 GiB
 * ============================================================
 */

setup_paging:

    /*
     * Clear page tables explicitly
     */

    mov edi, offset pml4_table

    xor eax, eax

    mov ecx, (4096 * 3) / 4

    rep stosd

    /*
     * PML4[0] -> PDPT
     */

    mov eax, offset pdpt_table

    or eax, 0x03

    mov dword ptr [pml4_table], eax

    /*
     * PDPT[0] -> PD
     */

    mov eax, offset pd_table

    or eax, 0x03

    mov dword ptr [pdpt_table], eax

    /*
     * Build 512 page directory entries
     *
     * Each entry maps 2 MiB.
     */

    mov edi, offset pd_table

    mov eax, 0x00000083

    mov ecx, 512

fill_pd:

    mov dword ptr [edi], eax

    mov dword ptr [edi + 4], 0

    add eax, 0x00200000

    add edi, 8

    loop fill_pd


/* ============================================================
 * LOAD GDT
 * ============================================================
 */

load_gdt:

    lgdt [gdt_descriptor]


/* ============================================================
 * ENABLE PAE
 * ============================================================
 */

enable_pae:

    mov eax, cr4

    or eax, 1 << 5

    mov cr4, eax


/* ============================================================
 * LOAD PML4 INTO CR3
 * ============================================================
 */

load_cr3:

    mov eax, offset pml4_table

    mov cr3, eax


/* ============================================================
 * ENABLE LONG MODE
 *
 * IA32_EFER = MSR 0xC0000080
 * LME       = bit 8
 * ============================================================
 */

enable_long_mode:

    mov ecx, 0xC0000080

    rdmsr

    or eax, 1 << 8

    wrmsr


/* ============================================================
 * ENABLE PAGING
 *
 * CR0.PG = bit 31
 * ============================================================
 */

enable_paging:

    mov eax, cr0

    or eax, 0x80000000

    mov cr0, eax


/* ============================================================
 * FAR JUMP TO LONG MODE
 *
 * Selector: 0x08
 * Destination: long_mode_start
 *
 * Memory operand contains:
 * 32-bit offset + 16-bit selector
 * ============================================================
 */

enter_long_mode:

    ljmp DWORD PTR [far_jump_pointer]


/* ============================================================
 * BOOT ERROR
 * ============================================================
 */

boot_error:

    cli

boot_halt:

    hlt

    jmp boot_halt


/* ============================================================
 * LONG MODE - 64 BIT
 * ============================================================
 */

.code64

long_mode_start:

    /*
     * Initialize segment registers
     */

    mov ax, 0x10

    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    /*
     * Initialize 64-bit stack
     */

    lea rsp, [rip + stack_top]

    and rsp, -16

    /*
     * Clear direction flag
     */

    cld

    /*
     * Prepare System V AMD64 ABI arguments
     *
     * RDI = Multiboot magic
     * RSI = Multiboot information address
     */

    mov edi, dword ptr [rip + boot_magic]

    mov esi, dword ptr [rip + mbi_ptr]

    /*
     * Call C kernel
     */

    call kmain


/* ============================================================
 * KERNEL HALT
 * ============================================================
 */

kernel_halt:

    cli

    hlt

    jmp kernel_halt


/* ============================================================
 * GDT - GLOBAL DESCRIPTOR TABLE
 * ============================================================
 */

.section .rodata
.align 8

gdt_start:

    /*
     * Null descriptor
     */

    .quad 0x0000000000000000

    /*
     * 64-bit Code Segment
     *
     * Selector: 0x08
     * L = 1
     * D = 0
     */

    .quad 0x00AF9A000000FFFF

    /*
     * Data Segment
     *
     * Selector: 0x10
     */

    .quad 0x00CF92000000FFFF

gdt_end:


/*
 * GDT Descriptor
 *
 * Used by LGDT in 32-bit mode.
 */

gdt_descriptor:

    .word gdt_end - gdt_start - 1

    .long gdt_start


/*
 * Far Jump Pointer
 *
 * 32-bit offset
 * 16-bit code selector
 */

.align 4

far_jump_pointer:

    .long long_mode_start

    .word 0x08


/* ============================================================
 * BSS - PAGE TABLES AND VARIABLES
 * ============================================================
 */

.section .bss
.align 4096


/*
 * PML4
 */

pml4_table:

    .skip 4096


/*
 * Page Directory Pointer Table
 */

pdpt_table:

    .skip 4096


/*
 * Page Directory
 */

pd_table:

    .skip 4096


/*
 * Multiboot variables
 */

.align 4

boot_magic:

    .skip 4

mbi_ptr:

    .skip 4


/* ============================================================
 * KERNEL STACK
 * ============================================================
 */

.align 16

stack_bottom:

    .skip 16384

stack_top:


.section .note.GNU-stack,"",@progbits

