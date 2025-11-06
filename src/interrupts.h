#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_
#include <stdint.h>
typedef struct {
	uint16_t offset_15_00;
	uint16_t selector;
	uint8_t  reserved;
	uint8_t  attributes;
	uint16_t offset_31_16;
} __attribute__((packed)) idt_desc;

typedef struct {
	uint16_t limit;
	uint32_t base_address;
} __attribute__((packed)) idt_reg;



#endif
