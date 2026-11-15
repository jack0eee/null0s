/*

        struttura MBI di multiboot (versione 1)

*/

#ifndef MULTIBOOT_H
#define MULTIBOOT_H

   /* 
   .------------------------------.
   |   Multiboot 1 magic number   |
   '------------------------------' */
   #define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

   /*
   .--------------------------------.
   |    Flag della struttura MBI    |
   '--------------------------------' */
   #define MULTIBOOT_INFO_MEMORY    (1 << 0)
   #define MULTIBOOT_INFO_BOOTDEV   (1 << 1)
   #define MULTIBOOT_INFO_CMDLINE   (1 << 2)
   #define MULTIBOOT_INFO_MODS      (1 << 3)
   #define MULTIBOOT_INFO_AOUT_SYMS (1 << 4)
   #define MULTIBOOT_INFO_ELF_SHDR  (1 << 5)
   #define MULTIBOOT_INFO_MEM_MAP   (1 << 6)

   /* 
   .-----------------------------------.
   |  Struttura Multiboot Information  |
   '-----------------------------------' */
   typedef struct multiboot_info
   {
        uint32_t flags       ; 
        uint32_t mem_lower   ;
        uint32_t mem_upper   ;
        uint32_t boot_device ;
        uint32_t cmdline     ;
        uint32_t mods_count  ;
        uint32_t mods_addr   ;

        /*
        .--------------------------.
        | Tabella simboli ELF/AOUT |
        '--------------------------' */
        union 
        {
            struct 
            {
                uint32_t tabsize   ;
                uint32_t strsize   ;
                uint32_t addr      ;
                uint32_t reserved  ;
            } aout ;

            struct
            {
                uint32_t num       ;
                uint32_t size      ;
                uint32_t addr      ;
                uint32_t shndx     ;
            } elf ;
        } syms ;

        uint32_t mmap_lenght       ;
        uint32_t mmap_addr         ;
        uint32_t drives_lenght     ;
        uint32_t drives_addr       ;
        uint32_t config_table      ;
        uint32_t boot_loader_name  ;
        uint32_t apm_table         ;
        uint32_t vbe_control_info  ;
        uint32_t vbe_mode_info     ;

        uint16_t vbe_mode          ;
        uint16_t vbe_interface_seg ;
        uint16_t vbe_interface_off ;
        uint16_t vbe_interface_len ;

   } __attribute__((packed)) multiboot_info_t ;

#endif

 
