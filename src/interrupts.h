#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_
#include <stdint.h>
#define MAS_SIZE 33
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

void idt_init(void);
void idt_set_desc(uint8_t vector, void *isr, uint8 flags);
void exception_handler(void);

#endif
