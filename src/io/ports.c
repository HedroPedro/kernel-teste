#include "ports.h"

uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ("in %b0, %w1"
					: "=a"(ret)
					: "Nd"(port)
					: "memory");
	return ret;
}

uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile ("in %w0, %w1"
					: "=a"(ret)
					: "Nd"(port)
					: "memory");
	return ret;
}

uint32_t inl(uint16_t port) {
	uint32_t ret;
	asm volatile ("in %0, %w1"
					: "=a"(ret)
					: "Nd"(port)
					: "memory");
	return ret;
}

void outb(uint16_t port, uint8_t data) {
	asm volatile ("out %w1, %b0" : : "a"(data), "Nd"(port) : "memory");	
}

void outw(uint16_t port, uint16_t data) {
	asm volatile ("out %w1, %w0" : : "a"(data), "Nd"(port) : "memory");	
}

void outl(uint16_t port, uint32_t data) {
	asm volatile ("out %w1, %0" : : "a"(data), "Nd"(port) : "memory");	
}

void io_wait(void) {
	outb(0x80, 0x0);
}
