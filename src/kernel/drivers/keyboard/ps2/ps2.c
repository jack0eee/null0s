/*
.---------------------------------------------------------------------.
|                                                                     |
|                                                                     |
|                              driver PS2                             |
|                                                                     |
|  API :                                                              |
|                                                                     |
|  keyboard_read_scancode()                                           |
|                                                                     |
|                                                                     |
'---------------------------------------------------------------------' */

#include "ps2.h"

//#include "device_io.h"
#include "io.h"

#define PS2_DATA   0x60
#define PS2_STATUS 0x64

unsigned short int keyboard_read_scancode() 
{
     /*
     .--------------------------------------------.
     | Il bit 0 del registro Status (0x64) indica |
     | se il buffer di output contiene un byte    |
     | disponibile.                               |
     '--------------------------------------------' */

     // unsigned char device_read(device_t *dev, unsigned int registro)

     while ((inb(PS2_STATUS) & 1) == 0)
     {
           // attendi un dato
     }

     return inb(PS2_DATA);
}

// ====---- EOF 

 
