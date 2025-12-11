#include "interrupts.h"

__attribute__((aligned(0x10)))
static idt_desc idt[256];
static idt_reg idtr;
extern void *isr_table[];


typedef int32_t (*service_fun)(uint32_t, uint32_t);

service_fun services[] = { read_file };

void idt_init(void) {
	idtr.base = (uint32_t) &idt[0];
	idtr.limit = (uint16_t) sizeof(idt_desc) * (MAX_IDT_SIZE - 1);
	for (uint8_t i = 0; i < 32; i++) {
		idt_set_desc(i, isr_table[i], 0x8E);
	}

	asm volatile ("lidt %0;" : : "m"(idtr));
	asm volatile ("sti;");
}

void idt_set_desc(uint8_t vector, void *isr, uint8_t flags) {
	idt_desc *desc = &idt[vector];
	desc->isr_low = (uint32_t) isr & 0xFF;
	desc->selector = 0x02;
	desc->reserved = 0;
	desc->attributes = flags;
	desc->isr_high = (uint32_t) isr >> 16;
}

void exception_handler(void) {
	asm volatile (
		"cli;\n"
		"hlt;\n");
}

int32_t get_service(uint32_t index, uint32_t arg0, uint32_t arg1) {
	if (index >= (sizeof(services)/sizeof(service_fun))) {
		exception_handler();
		return -1;
	}
	return services[index](arg0, arg1);
}

int32_t read_file(uint32_t arg0, uint32_t arg1) {
	return 'a';
}
