#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_
#include <stdint.h>
typedef struct {
	uint8_t  base_31_24;
	uint8_t  limit_19_16;
	uint8_t  type_flags;
	uint8_t  base_23_16;
	uint16_t base_15_00;
	uint16_t limit_15_00;
} __attribute__((packed)) gdt_descriptor;

typedef struct {
	uint16_t descrpitor_size;
	uint32_t *descriptor_table;
} __attribute__((packed)) gdt_info; 
#endif
