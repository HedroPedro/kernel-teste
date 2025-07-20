#include <stdbool.h>
#include <stdint.h>

#define VGA_COL 80
#define VGA_ROW 25
#define VGA_ADDR 0xB8000


typedef char color_code;
typedef unsigned short color; 

color current_color = 0x0;

enum COLORS {
	BLACK_COLOR  = 0,
	RED_COLOR    = 1,
	GREEN_COLOR  = 2,
	YELLOW_COLOR = 3,
	BLUE_COLOR   = 4,
        PURPLE_COLOR = 5,
	CYAN_COLOR   = 6,
	WHITE_COLOR  = 7
}

static void terminal_init(void) {
	uint_16 current_address = VGA_ADDR;
	for (int i = 0; i < VGA_COL; i++) {
		for(int j = 0; j < VGA_ROW; j++) {
			*(current_address) = 0;
			current_address += 2;
		}
	}
}

static inline void terminal_color(color_code bg, color_code fg) {
	current_color = ((bg<<4)|fg)
}

static void terminal_write(const char *str, color_code bg, color_code fg) {
	char c;
	uint_16 i = 0;	
	uint_16 current_address = VGA_ADDR;
	terminal_color(bg, fg);

	while(c = str[i]) {
		i++
		*(current_address++) = c;
		*(current_address++) = current_color;
	}
}


void kernel_main(void) {
  	terminal_init();
	terminal_write("Ola mundo!", BLACK_COLOR, WHITE_COLOR);
}
