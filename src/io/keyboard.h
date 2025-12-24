#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include <stdint.h>
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_PORT 	(KEYBOARD_DATA_PORT)
void get_key(void);
#endif
