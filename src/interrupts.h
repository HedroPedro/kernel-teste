#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_
#include <stdint.h>
#include <stdbool.h>
#define MAX_IDT_SIZE 47
typedef struct {
	uint16_t isr_low;
	uint16_t selector;
	uint8_t  reserved;
	uint8_t  attributes;
	uint16_t isr_high;
} __attribute__((packed)) idt_desc;

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idt_reg;

void idt_init(void);
void idt_set_desc(uint8_t vector, void *isr, uint8_t flags);
void exception_handler(void);

#endif
