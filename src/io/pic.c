#include "pic.h"
#define OFFSET1 0x20
#define OFFSET2 0x28

void pic_init(void) {
	outb(PIC1_CMD, ICW1);
	io_wait();
	outb(PIC2_CMD, ICW1);
	io_wait();

}
