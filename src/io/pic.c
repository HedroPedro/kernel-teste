#include "pic.h"
#define OFFSET1 0x20
#define OFFSET2 0x28

void pic_init(void) {
	outb(PIC1_CMD, ICW1);
	io_wait();
	outb(PIC2_CMD, ICW1);
	io_wait();
	outb(PIC1_DATA, OFFSET1);
	io_wait();
	outb(PIC2_DATA, OFFSET2);
	io_wait();
	outb(PIC1_DATA, 1 << CASCADE_IRQ);
	io_wait();
	outb(PIC2_DATA, CASCADE_IRQ);
	io_wait();
	outb(PIC1_DATA, ICW4);			
	io_wait();
	outb(PIC2_DATA, ICW4);	
	io_wait();

	outb(PIC1_DATA, 0);
	outb(PIC2_DATA, 0);
}

void pic_disable(void) {
	outb(PIC1_DATA, 0xFF);
	outb(PIC2_DATA, 0xFF);
}

void pic_sendEOI(uint8_t irq) {
	if (irq >= 8)
		outb(PIC2_CMD, PIC_EOI);
	outb(PIC1_CMD, PIC_EOI);
}
