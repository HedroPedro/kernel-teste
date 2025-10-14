#include "terminal.h"
static uint16_t current_color = 0;
static uint8_t current_column = 0;
static uint8_t current_line = 0;
static uint16_t *terminal_address = (uint16_t*) 0xB8000;

void write_char(const char chr) {
    terminal_address[current_line*80+current_column] = current_color | chr;
    current_column++;
    if (current_column == MAX_COLUMNS) {
        current_column ^= current_column;
        current_line++;
        if (current_line == MAX_LINES) {
            current_line ^= current_line;
        }
    }
}

void write_text(const char *text) {
    char c;
    while((c = (*text))) {
        write_char(c);
        text++;
    }
}

void set_color(uint8_t color) {
    current_color = (uint16_t) (color<<8);
}
