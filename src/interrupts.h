#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_
#include <stdint.h>
#include <stdbool.h>
#define MAX_IDT_SIZE 48
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
int32_t get_service(uint32_t index, uint32_t arg2, uint32_t arg3);
int32_t read_file(uint32_t fd, uint32_t bytes);
#endif
