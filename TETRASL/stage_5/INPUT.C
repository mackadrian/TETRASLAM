/**
 * @file INPUT.C
 * @brief contains the keyboard input library for TETRASLAM.
 * @author Mack Bautista
 */

#include "input.h"

/*
----- FUNCTION: user_input -----
Purpose:    changes the character pointer passed if a valid key was pressed.
Parameters: char input      pointer to a character varaible
Limitations: - All of the keyboard inputs will be used inside the table.
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
    case KEY_ARROW_LEFT:
    case KEY_ARROW_RIGHT:
        *input = ch;
        break;
    default:
        break;
    }
}