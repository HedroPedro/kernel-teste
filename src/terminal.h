#ifndef TERMINAL_H_
#define TERMINAL_H_
#include <stdint.h>

void write_on_terminal(char *str, uint8_t x, uint8_t y);
void set_color(uint8_t color); 

#endif
