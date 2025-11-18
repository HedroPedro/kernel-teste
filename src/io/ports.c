#include "ports.h"

inline uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ("inb %b0, %w1"
					: "=a"(ret)
					: "Nd"(port)
					: "memory");
	return ret;
}

inline uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile ("inw %w0, %w1"
					: "=a"(ret)
					: "Nd"(port)
					: "memory");
	return ret;
}

inline uint32_t inb(uint16_t port) {
	uint32_t ret;
	asm volatile ("inb %l0, %w1"
					: "=a"(ret)
					: "Nd"(port)
					: "memory");
	return ret;
}

inline void outb(uint16_t port, uint8_t data) {
	asm volatile ("outb %w1, %b0" : : "a"(val), "Nd"(port) : "memory");	
}

inline void outw(uint16_t port, uint16_t data) {
	asm volatile ("outb %w1, %w0" : : "a"(val), "Nd"(port) : "memory");	
}

inline void outl(uint16_t port, uint32_t data) {
	asm volatile ("outb %w1, %l0" : : "a"(val), "Nd"(port) : "memory");	
}
