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

/*
.-----------------.
| FakeApplication |
'-----------------' */
#include "gameOfLife.h"
#include "printIntSizeof.h"
#include "printInfoMultibootv1.h"
#include "vgaDriverTest.h"
#include "ps2DriverTest.h"

// #include "multiboot.h"


void kmain(uint32_t magic, uint32_t mbi_addr)
{
     char *banner = "null0s 0.1 starting...\n" ;

     /*
     .----------------------------------------.
     | Inizializzazione struttura Console VGA |
     '----------------------------------------' */
     vga_console_init();
     vga_buffer_init();

     /*
     .------------------------------------------.
     |              Banner null0s               |
     '------------------------------------------' */
     vga_console_setposition (0,0);
     vga_console_setcolor ( VGA_COLOR_BLUE, VGA_COLOR_WHITE);
     printf("%s", banner);

     vga_cursor_enable (0, 15);

     /*
     .---------------------------------------------------------.
     |               Debugging Application Fake                |
     +---------------------------------------------------------+
     |  1) printInfoMultibootv1                                |
     |  2) vgaDriverTest                                       |
     |  3) gameOfLife                                          |
     |  4) printIntSizeof                                      | 
     |  5) ps2DriverTest                                       |
     '---------------------------------------------------------' */
     uint8_t idApplication = 5;
     switch (idApplication) 
     {
        case 1  : printInfoMultibootv1 (magic, mbi_addr); break;
        case 2  : vgaDriverTest();                        break;
        case 3  : gameOfLife();                           break;
        case 4  : printIntSizeof();                       break;
        case 5  : ps2DriverTest();                        break;
        default : printf("no application.");
     }



     for (;;)
     {   
            __asm__ __volatile__("hlt");
     }
}

/* EOF */

