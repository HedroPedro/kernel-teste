#ifndef PORTS_H_
#define PORTS_H_
#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ("in %b0, %w1"
					: "=a"(ret)
					: "Nd"(port)
					: "memory");
	return ret;
}

static inline uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm inline volatile ("in %w0, %w1"
					: "=a"(ret)
					: "Nd"(port)
					: "memory");
	return ret;
}

static inline uint32_t inl(uint16_t port) {
	uint32_t ret;
	asm inline volatile ("in %0, %w1"
					: "=a"(ret)
					: "Nd"(port)
					: "memory");
	return ret;
}

static inline void outb(uint16_t port, uint8_t data) {
	asm inline volatile ("out %w1, %b0" : : "a"(data), "Nd"(port) : "memory");	
}

static inline void outw(uint16_t port, uint16_t data) {
	asm inline volatile ("out %w1, %w0" : : "a"(data), "Nd"(port) : "memory");	
}

static inline void outl(uint16_t port, uint32_t data) {
	asm inline volatile ("out %w1, %0" : : "a"(data), "Nd"(port) : "memory");	
}

static inline void io_wait(void) {
	outb(0x80, 0x0);
}
#endif
