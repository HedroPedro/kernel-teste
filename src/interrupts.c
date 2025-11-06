#include "interrupts.h"

__attribute__((aligned(0x10)))
static idt_desc idt[256];
static idt_reg idtr;
