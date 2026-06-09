
#ifndef IO_H
#define IO_H

/* --------------

inb/outb
inw/outw/inl/outl
readl/writel (MMIO con barrier)
memory barrier (mb(),wmb(),rmb())

-------------------- */ 

// static inline uint8_t inb(uint16_t port);
// static inline void outb(uint16_t port, uint8_t val);

unsigned char inb(unsigned short int port);
void outb(unsigned short int port, unsigned char value);

#endif 
