/*
.-----------------------------------------------------.
|                                                     |
|                                                     |
|                   PS2 Driver Test                   |
|                                                     |
|                                                     |
'-----------------------------------------------------' */

#include "stdio.h"
#include "stdint.h"

//--------
#include "ps2.h" 
//--------------------

#include "ps2DriverTest.h"

void ps2DriverTest()
{
    printf ("PS2 Driver Test\n");
    printf ("Premi qualche tasto della tastiera :\n\n");

    while (1)
    {
          uint8_t scancode;

          scancode = keyboard_read_scancode();

          printf("scancode: %x\n", scancode); 
    }
}

/* EOF */

