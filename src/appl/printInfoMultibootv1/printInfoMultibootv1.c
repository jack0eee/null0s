/*
.-----------------------------------------------------.
|                                                     |
|                                                     |
|                       kernel                        |
|                                                     |
|                                                     |
'-----------------------------------------------------' */

#include "stdio.h"
#include "stdint.h"

#include "printInfoMultibootv1.h"

#include "multiboot.h"

int8_t printInfoMultibootv1(uint32_t magic, uint32_t mbi_addr)
{

     /*
     .---------------------------------------------------.
     | Definizione variabile di tipo multiboot_info_t    |
     '---------------------------------------------------' */
  // multiboot_info_t *mbi = (multiboot_info_t *)mbi_addr;
     multiboot_info_t *mbi = (multiboot_info_t *)(uintptr_t)mbi_addr;

     /*
     .--------------------------------------.
     | Parametri di interfaccia (EAX, EBX)  |
     '--------------------------------------' */
     printf("\n");
     printf("+------------------------------------------+\n");
     printf("| Parametri di interfaccia MB-1 (eax, ebx) |\n");
     printf("+------------------------------------------+\n");
     printf("| magic        : [0x%x]\n", magic); 
     printf("| MBI address  : [0x%x]\n", mbi_addr);

     //   uint32_t flags       ;

     /*
     .-----------------------------------------------.
     | Verifica disponibilita' informazioni memoria. |  
     '-----------------------------------------------' */
     if (mbi->flags & MULTIBOOT_INFO_MEMORY)
     {
         printf("\n");
         printf("+------------------------------------------+\n");
         printf("| Informazioni Memoria [disponibile]       |\n");
         printf("+------------------------------------------+\n");
         printf("| mem_lower    : [%d]kb\n", mbi->mem_lower);
         printf("| mem_upper    : [%d]kb\n", mbi->mem_upper);
         printf("+------------------------------------------+\n");
     } 
     else
     {
         printf("\n");
         printf("+------------------------------------------+\n");
         printf("| Informazioni Memoria [*non* disponibile] |\n");
         printf("+------------------------------------------+\n");
     }

/*
   #define MULTIBOOT_INFO_MEMORY    (1 << 0)
   #define MULTIBOOT_INFO_BOOTDEV   (1 << 1)
   #define MULTIBOOT_INFO_CMDLINE   (1 << 2)
   #define MULTIBOOT_INFO_MODS      (1 << 3)
   #define MULTIBOOT_INFO_AOUT_SYMS (1 << 4)
   #define MULTIBOOT_INFO_ELF_SHDR  (1 << 5)
   #define MULTIBOOT_INFO_MEM_MAP   (1 << 6)
*/
     /*
     .-----------------------------------------.
     | Verifica disponibilita' di INFO BOOTDEV |
     '-----------------------------------------' */
     if (mbi->flags & MULTIBOOT_INFO_BOOTDEV)
     {
         printf("| boot_device  : [%s]\n", mbi->boot_device       );
     }

     /*
     .-----------------------------------------.
     | Verifica disponibilita' di INFO CMDLINE |
     '-----------------------------------------' */
     if (mbi->flags & MULTIBOOT_INFO_CMDLINE)
     {
         printf("| cmdline      : [%s]\n", mbi->cmdline           );
     }

     /*
     .--------------------------------------.
     | Verifica disponibilita' di INFO MODS |
     '--------------------------------------' */
     if (mbi->flags & MULTIBOOT_INFO_MODS)
     {
         printf("| mods_count   : [%s]\n", mbi->mods_count        );
         printf("| mods_addr    : [%x]\n", mbi->mods_addr         );
     }

   //...

     /*
     .-----------------------------------------.
     | Verifica disponibilita' di INFO MEM MAP |
     '-----------------------------------------' */
     if (mbi->flags & MULTIBOOT_INFO_MEM_MAP)
     {
         printf("| mmap_lenght  : [%d]\n", mbi->mmap_lenght       );
         printf("| mmap_addr    : [%x]\n", mbi->mmap_addr         );
     }

/*
     printf("+-----------------------------------------------------------+\n");
     printf("| drives_lenght    : [%d]\n", mbi->drives_lenght     );
     printf("| drives_addr      : [%x]\n", mbi->drives_addr       );
     printf("+-----------------------------------------------------------+\n");
*/
     printf("| config_table     : [%s]\n", mbi->config_table      );
     printf("| boot_loader_name : [%s]\n", mbi->boot_loader_name  );
     printf("| apm_table        : [%s]\n", mbi->apm_table         );
     printf("+-----------------------------------------------------------+\n");

/*
     printf("| vbe_control_info : [%s]\n", mbi->vbe_control_info  );
     printf("| vbe_mode_info    : [%s]\n", mbi->vbe_mode_info     );
     printf("| vbe_mode         : [%d]\n", mbi->vbe_mode          );
     printf("| vbe_interface_seg: [%d]\n", mbi->vbe_interface_seg ); 
     printf("| vbe_interface_off: [%d]\n", mbi->vbe_interface_off );
     printf("| vbe_interface_len: [%d]\n", mbi->vbe_interface_len );
     printf("+-----------------------------------------------------------+\n");
*/
     return 0;
}

/* EOF */

