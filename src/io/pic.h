#ifndef PIC_H_
#define PIC_H_
#include <stdint.h>
#include "ports.h"
#define PIC1_CMD  0x20
#define PIC1_DATA (PIC1_CMD+1)
#define PIC2_CMD  0xA0
#define PIC2_DATA (PIC2_CMD+1)
#define PIC_EOI   0x20

#define ICW1_INIT   0x1
#define ICW1_SINGLE 0x2
#define ICW1_SIZE   0x4
#define ICW1_MODE   0x8
#define ICW1_4      0x10
#define ICW1	    (ICW1_INIT | ICW1_SINGLE | ICW1_SIZE | ICW1_MODE | ICE1_4)
#define ICW4_8086   0x1
#define ICW4_AUTO   0x2
#define ICW4_BUFF   0xC
#define ICW4_NEST   0x10
#define ICW4	    (ICW4_8086 | ICW4_AUTO | ICW4_BUFF |ICW4_NEST)
#define CASCADE_IRQ 2

void pic_init(void);
void pic_disable(void);
void pic_sendEOI(uint8_t irq);
#endif
