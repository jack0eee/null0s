
#include "device_io.h"
#include "io.h"

/*
 * Funzione Read Registro Dispositivo 
 */
unsigned char device_read(device_t *dev, unsigned int registro)
{
     switch (dev->type)
     {
         case DEV_PMIO:
              return inb (dev->port_base + registro);

         case DEV_MMIO:
              return *((volatile unsigned char *)(dev->mmio_base + registro));
     }
     return 0;
};

/*
 * Funzione Write Registro Dispositivo
 */
void device_write(device_t *dev, unsigned int registro, unsigned char valore)
{
     switch (dev->type)
     {
         case DEV_PMIO:
              outb (dev->port_base + registro, valore );
              break;

         case DEV_MMIO:
              *((volatile unsigned char *)(dev->mmio_base + registro)) = valore;
              break;
     }
};



