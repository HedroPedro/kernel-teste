#include <stdbool.h>
#include <stdint.h>

void kmain(void) {
    const uint16_t color = 0x0F00;
    const char* hello = "Hello c world!";
    uint16_t* vga = (uint16_t*)0xB8000;
    for (int i = 0; i<14;++i)
        vga[i] = color | hello[i];

}
