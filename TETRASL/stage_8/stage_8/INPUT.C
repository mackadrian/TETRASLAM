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
    - Updates the character pointer passed to the function if a valid key is pressed.
      Valid keys include space, escape, uppercase 'C', lowercase 'c', left and right arrow keys.

Details:
    - The function checks if a key is pressed using the 'Cconis()' library function.
    - It reads the key as a long word to identify extended keys, specifically the left and right arrow keys.
    - Since the ASCII code is stored in the least significant byte (LSByte) of the long word,
      the function checks for this value and, if needed, extracts the extended key from the most significant byte (MSByte).
    - If the key is recognized, it updates the character pointer with the corresponding key.

Parameters:
    - char *input:     A pointer to a character variable that will be updated with the pressed key.

Limitations:
    - Assumes the use of 'Cconis()' and 'Cnecin()' for input handling.
    - Handles only predefined keys and scancodes; unrecognized keys are ignored.
    - The function does not support simultaneous key presses or modifier keys.
*/
void user_input(char *input)
{
    char ch, extended_key;
    long key_code;

    if (!Cconis())
    {
        return;
    }

    key_code = Cnecin();
    ch = (char)key_code;

    if (ch == 0x00)
    {
        extended_key = (char)(key_code >> 16);

        switch (extended_key)
        {
        case KEY_LEFT_ARROW:
        case KEY_RIGHT_ARROW:
            *input = extended_key;
            break;
        default:
            break;
        }
        return;
    }

    switch (ch)
    {
    case KEY_SPACE:
    case KEY_ESC:
    case KEY_UPPER_C:
    case KEY_LOWER_C:
        *input = ch;
        break;
    default:
        break;
    }
}