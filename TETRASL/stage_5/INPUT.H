#ifndef INPUT_H
#define INPUT_H

#include "types.h"
#include <osbind.h>

#define KEY_NULL 0x00
#define KEY_SPACE 0x20
#define KEY_ESC 0x1B
#define KEY_UPPER_C 0x43
#define KEY_LOWER_C 0x63
#define KEY_ARROW_LEFT 0x4B
#define KEY_ARROW_RIGHT 0x4D

void user_input(char *input);

#endif