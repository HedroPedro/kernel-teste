#ifndef TERMINAL_H_
#define TERMINAL_H_
#include <stdint.h>

#define MAX_COLUMNS 25
#define MAX_LINES   80

void write_char(const char chr); 
void write_text(const char *text);
void set_color(uint8_t color);

#endif
