#include "kernel.h" 

void kmain(void) {
	idt_init();
	const uint8_t color = 0x0F;
	const char* hello = "Hello c world!";
	set_color(color);
	write_text(hello); 
}
