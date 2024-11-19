/**
 * @file INPUT.C
 * @brief contains the keyboard input library for TETRASLAM.
 * @author Mack Bautista
 */

#include "input.h"
#include <stdio.h>

/*
----- FUNCTION: user_input -----
Purpose:
    - Changes the character pointer passed if a valid key is pressed. Valid keys are space, escape,
      uppercase 'C', lowercase 'c', left arrow, and right arrow.
Details:
    - The function checks if a key is pressed, and if it is a valid key from the predefined set,
      it updates the character pointer with the pressed key.

Parameters:
    - char *input:     A pointer to a character variable that will be updated with the pressed key.

Limitations:
    - All of the keyboard inputs will be used inside the table.
    - The function does not handle invalid or unrecognized keys.
*/
void user_input(char *input)
{
    char ch;
    if (!Cconis())
    {
        return;
    }

    ch = (char)Cnecin();
    switch (ch)
    {
    case KEY_SPACE:
    case KEY_ESC:
    case KEY_UPPER_C:
    case KEY_LOWER_C:
    case KEY_UPPER_M:
    case KEY_LOWER_M:
    case KEY_UPPER_N:
    case KEY_LOWER_N:
        *input = ch;
        break;
    default:
        break;
    }
}