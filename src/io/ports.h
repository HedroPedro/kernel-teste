#ifndef PORTS_H_
#define PORTS_H_
#include <stdint.h>

inline uint8_t inb(uint16_t port);

inline uint16_t inw(uint16_t port);

inline uint32_t indw(uint16_t port);

inline void outb(uint16_t port, uint8_t data);

inline void outw(uint16_t port, uint16_t data);

inline void outl(uint16_t port, uint32_t data);
#endif
