#ifndef TERMINAL_H_
#define TERMINAL_H_
#include <stdint.h>

#define MAX_COLUMNS 25
#define MAX_LINES   80
#define BLINK	    128

enum FG_COLORS {
	FG_UNDERLINE = 1,
	FG_BLUE,
	FG_GREEN,
	FG_CYAN,
	FG_RED,
	FG_PURPLE,
	FG_ORANGE,
	FG_INTENSITY
};

enum BG_COLORS {
	BG_BLUE = 1<<4,
	BG_GREEN,
	BG_CYAN,
	BG_RED,
	BG_PURPLE,
	BG_ORANGE
};

void write_char(const char chr); 
void write_text(const char *text);
void set_color(uint8_t color);

#endif
