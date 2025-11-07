#include "interrupts.h"

__attribute__((aligned(0x10)))
static idt_desc idt[256];
static idt_reg idtr;
extern void *idt_table;

void idt_init(void) {
	idtr.base = (uint32_t) idt[0];
	idtr.limit = (uint16_t) sizeof(idt_desc) * (MAX_IDT_SIZE - 1)
}

void idt_set_desc(uint8_t vector, void *isr, uint8 flags) {
	idt_desc *desc = &idt[vector];
	dec->isr_low = (uint16_t) isr & 0xFF;
	dec->selector = 0x08;
	dec->reserved = 0;
	dec->atributes = flags;
	dec->isr_high = (uint16_t) isr >> 16;
}

void exception_handler(void) {
	asm volatile (
		"cli\n"
		"hlt\n"
		:::)
}
