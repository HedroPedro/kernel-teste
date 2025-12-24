#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_
#include <stdint.h>
#include <stdbool.h>
#define MAX_IDT_SIZE 48
typedef struct idt_desc {
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

extern service_fun services[] = { read_file, write_file, read_write_file };

void idt_init(void);
void idt_set_desc(uint8_t vector, void *isr, uint8_t flags);
void exception_handler(void);
extern uint32_t read_file();
extern uint32_t write_file();
extern uint32_t read_write_file();
#endif
