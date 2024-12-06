/**
 * @file INPUT.C
 * @brief contains the keyboard input library for TETRASLAM.
 * @author Mack Bautista
 */

#include "input.h"
#include <stdio.h>

/*
----- FUNCTION: check_input_ready -----
Purpose:
    - Checks if there is a key press available for reading.

Details:
    - Uses the 'Cconis()' function to determine if there is any input ready to be processed.

Returns:
    - Returns 1 if a key is ready, 0 otherwise.
*/
int check_input_ready()
{
    return Cconis();
}

/*
----- FUNCTION: get_input -----
Purpose:
    - Retrieves the pressed key, including handling extended keys (e.g., arrow keys).

Details:
    - Uses 'Cnecin()' to get the key code.
    - If the key code represents an extended key (e.g., left or right arrow), it extracts the key from the most significant byte (MSByte).
    - If the key is a regular ASCII character, it returns it directly.

Returns:
    - Returns the ASCII value of the pressed key (or extended key value).
*/
char get_input()
{
    long key_code = Cnecin();
    char ch = (char)key_code;

    if (ch == 0x00)
    {
        char extended_key = (char)(key_code >> 16);
        switch (extended_key)
        {
        case KEY_LEFT_ARROW:
        case KEY_RIGHT_ARROW:
            return extended_key;
        default:
            break;
        }
    }

    switch (ch)
    {
    case KEY_SPACE:
    case KEY_ESC:
    case KEY_UPPER_C:
    case KEY_LOWER_C:
        return ch;
        break;
    default:
        break;
    }
}

/*
----- FUNCTION: user_input -----
Purpose:
    - Updates the character pointer with the pressed key if a valid key is detected.

Details:
    - Checks if input is available using 'check_input_ready'.
    - Retrieves the key code using 'get_input', and updates the input character pointer.

Parameters:
    - char *input: Pointer to the character variable that will hold the pressed key.

Limitations:
    - Assumes input handling functions 'check_input_ready' and 'get_input' are available.
    - Only processes predefined keys and scancodes; unrecognized keys are ignored.
*/
void user_input(char *input)
{
    char key;

    if (!check_input_ready())
    {
        return;
    }

    key = get_input();
    if (key != KEY_NULL)
    {
        *input = key;
    }
}