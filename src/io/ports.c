#include "io.h"

uint8_t inb(uint16_t port) {
	uint8_t res;
	asm inline volatile("in %1, %0\n" 
		    : "=a" (res)
		    : "dN" (port) 
			);
	return res;
}

uint16_t inw(uint16_t port) {
	uint16_t res;
	asm inline volatile("in %1, %0\n"
		    : "=a" (res)
		    : "dN" (port)
			);
	return res;
}

uint32_t indw(uint16_t port) {
	uint32_t res;
	asm inline volatile("in %1, %0\n"
		: "=a" (res)
		: "dN" (port)
		);
	return res;
}

void outb(uint16_t port, uint8_t data) {
	asm inline volatile("out %0, %1\n"
				:
				: "a"(data), "dN"(port)
			);
}

void outw(uint16_t port, uint16_t data) {
	asm inline volatile("out %0, %1\n"
				:
				: "a"(data), "dN"(port)
			);
}


void outl(uint16_t port, uint32_t data) {
	asm inline volatile("out %0, %1\n"
				:
				: "a"(data), "dN"(port)
			);
}
