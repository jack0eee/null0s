
/* device_io.h | Astrazione PMIO/MMIO */

#ifndef DEVICE_IO_H
#define DEVICE_IO_H

/*
 * Tipo di Device: PMIO|MMIO
 */
typedef enum {
    DEV_PMIO,
    DEV_MMIO
} io_type_t;

typedef struct {
    io_type_t type ;
    union {
        unsigned short int port_base;
        void *mmio_base;
    };
} device_t;

/*
 * Funzione Read Registro Dispositivo 
 */
unsigned char device_read(device_t *dev, unsigned int registro);

/*
 * Funzione Write Registro Dispositivo
 */
void device_write(device_t *dev, unsigned int registro, unsigned char valore);


#endif
