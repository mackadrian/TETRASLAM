/**
 * @file TETRASL.C
 * @brief contains TETRASLAM's main game loop.
 * @author Mack Bautista
 */

#include "input.h"
#include "render.h"
#include "events.h"
#include "types.h"
#include "layout.h"
#include <osbind.h>

void init_starting_model(Model *model);
void process_async_events(Model *model, char ch);
void process_sync_events(Model *model);
UINT32 get_time();

/*
----- FUNCTION: main -----
Purpose:
    - Main game loop of TETRASLAM.

Details:
    - The function starts the game, initializing the game model, rendering the screen, and processing user inputs.
    - It contains a loop that listens for keypresses, processes the game events asynchronously and synchronously,
      and updates the screen accordingly. The game will continue until the user chooses to quit (presses ESC).

Limitations:
    - Requires proper hardware/OS to handle the graphics and input events.
*/
main()
{
    Model model;
    UINT32 time_then, time_now, time_elapsed;
    UINT32 *base_32 = (UINT32 *)Physbase();
    UINT16 *base_16 = (UINT16 *)Physbase();
    UINT8 *base_8 = (UINT8 *)Physbase();

    char ch = KEY_NULL;
    bool user_quit = FALSE;

    clear_screen(base_32);
    init_starting_model(&model);
    render(&model, base_32, base_16, base_8);

    time_then = get_time();
    while (!user_quit)
    {
        user_input(&ch);
        process_async_events(&model, ch);

        time_now = get_time();
        time_elapsed = time_now - time_then;
        time_then = time_now;

        if (time_elapsed > 1)
        {
            process_sync_events(&model);
            clear_screen(base_32);
            render(&model, base_32, base_16, base_8);

            if (fatal_tower_collision(&model.tower))
            {
                break;
            }

            time_then = time_now;
        }

        ch = KEY_NULL;
        user_input(&ch);
        if (ch == KEY_ESC)
        {
            clear_screen(base_32);
            user_quit = TRUE;
        }
    }

    return 0;
}

/*
----- FUNCTION: process_async_events -----
Purpose:
    - Processes the asynchronous events based on keyboard inputs.

Details:
    - The function takes the user input and processes the corresponding asynchronous events, such as moving the active piece
      or cycling through different pieces based on key presses.

Parameters:
    - Model *model:    Pointer to initialized game model.
    - char ch:        Keyboard input from user.

Limitations:
    - Only handles input events for moving, dropping, and cycling pieces.
*/
void process_async_events(Model *model, char ch)
{
    switch (ch)
    {
    case KEY_UPPER_N:
    case KEY_LOWER_N:
        move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
        break;
    case KEY_UPPER_M:
    case KEY_LOWER_M:
        move_active_piece(&model->active_piece, &model->playing_field, &model->tower, RIGHT);
        break;
    case KEY_SPACE:
        drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
        break;
    case KEY_UPPER_C:
    case KEY_LOWER_C:
        cycle_active_piece(&model->active_piece, model->player_pieces, &model->playing_field, &model->tower);
        break;
    default:
        break;
    }
}

/*
----- FUNCTION: process_sync_events -----
Purpose:
    - Processes the synchronized events to update the model.

Details:
    - The function checks if the active piece has merged with the tower, and if so, resets the active piece. It also clears
      completed rows after the active piece has merged.

Parameters:
    - Model *model:     Pointer to initialized game model.

Limitations:
    - Assumes the active piece will always be merged once it reaches the tower.
*/
void process_sync_events(Model *model)
{
    if (model->active_piece.merged)
    {
        reset_active_piece(&model->active_piece, model->player_pieces, &model->playing_field, &model->tower);
    }

    clear_completed_rows(&model->tower, &model->active_piece);

    update_counter(&model->counter, &model->tower);
}

/*
----- FUNCTION: get_time -----
Author: Paul Pospisil

Purpose:
    - Retrieves the current time from the CPU clock through supervisor access.

Details:
    - This function accesses the system timer, which is automatically incremented 70 times per second, and retrieves
      the current value of the timer.

Return:
    - UINT32:     The current system time.

Limitations:
    - Supervisor mode must be exited after usage.
*/
UINT32 get_time()
{
    UINT32 time_now;
    UINT32 old_ssp;
    UINT32 *timer = (UINT32 *)0x462; /*address of a long word that is auto incremented 70 times per second */

    old_ssp = Super(0); /* enter privileged mode */
    time_now = *timer;
    Super(old_ssp); /* exit privileged mode */

    return time_now;
}

/*
----- FUNCTION: init_starting_model -----
Purpose:
    - Initializes the model based on the values defined by the user.

Details:
    - The function sets up the initial configuration of the game, including the tetrominoes, playing field, tower, and score counter.
    - It also sets up the tiles of the tower and initializes the player pieces.

Parameters:
    - Model *model:   Pointer to the game model.

Limitations:
    - Assumes the game properties and pieces are correctly initialized based on the values defined.
*/
void init_starting_model(Model *model)
{
    initialize_tetromino(&model->active_piece, 285, 41, 16, 61, I_PIECE);
    initialize_field(&model->playing_field, 224, 40, 153, 303);
    initialize_counter(&model->counter, 224 + 153 + 32, 40, 78);

    initialize_tetromino(&model->player_pieces[0], 285, 41, 16, 61, I_PIECE);
    initialize_tetromino(&model->player_pieces[1], 285, 41, 31, 46, J_PIECE);
    initialize_tetromino(&model->player_pieces[2], 285, 41, 31, 46, L_PIECE);
    initialize_tetromino(&model->player_pieces[3], 285, 41, 31, 31, O_PIECE);
    initialize_tetromino(&model->player_pieces[4], 285, 41, 45, 31, S_PIECE);
    initialize_tetromino(&model->player_pieces[5], 285, 41, 45, 31, T_PIECE);
    initialize_tetromino(&model->player_pieces[6], 285, 41, 45, 31, Z_PIECE);

    /*Plotting tiles */
    initialize_tower(&model->tower, 78);
    /*Row 4*/
    initialize_tile(&model->tower, &model->tower.tiles[0], 225, 41 + (15 * 3));
    initialize_tile(&model->tower, &model->tower.tiles[1], 225 + (15 * 9), 41 + (15 * 3));
    /*Row 5*/
    initialize_tile(&model->tower, &model->tower.tiles[2], 225, 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[3], 225 + (15 * 2), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[4], 225 + (15 * 3), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[5], 225 + (15 * 6), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[6], 225 + (15 * 7), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[7], 225 + (15 * 9), 41 + (15 * 4));
    /*Row 6*/
    initialize_tile(&model->tower, &model->tower.tiles[8], 225 + (15 * 3), 41 + (15 * 5));
    initialize_tile(&model->tower, &model->tower.tiles[9], 225 + (15 * 4), 41 + (15 * 5));
    initialize_tile(&model->tower, &model->tower.tiles[10], 225 + (15 * 5), 41 + (15 * 5));
    initialize_tile(&model->tower, &model->tower.tiles[11], 225 + (15 * 6), 41 + (15 * 5));
    /*Row 7*/
    initialize_tile(&model->tower, &model->tower.tiles[12], 225 + 15, 41 + (15 * 6));
    initialize_tile(&model->tower, &model->tower.tiles[13], 225 + (15 * 8), 41 + (15 * 6));
    /*Row 8*/
    initialize_tile(&model->tower, &model->tower.tiles[14], 225, 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[15], 225 + (15 * 2), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[16], 225 + (15 * 3), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[17], 225 + (15 * 4), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[18], 225 + (15 * 5), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[19], 225 + (15 * 6), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[20], 225 + (15 * 7), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[21], 225 + (15 * 9), 41 + (15 * 7));
    /*Row 9*/
    initialize_tile(&model->tower, &model->tower.tiles[22], 225, 41 + (15 * 8));
    initialize_tile(&model->tower, &model->tower.tiles[23], 225 + (15 * 2), 41 + (15 * 8));
    initialize_tile(&model->tower, &model->tower.tiles[24], 225 + (15 * 3), 41 + (15 * 8));
    initialize_tile(&model->tower, &model->tower.tiles[25], 225 + (15 * 6), 41 + (15 * 8));
    initialize_tile(&model->tower, &model->tower.tiles[26], 225 + (15 * 7), 41 + (15 * 8));
    initialize_tile(&model->tower, &model->tower.tiles[27], 225 + (15 * 9), 41 + (15 * 8));
    /*Row 10*/
    initialize_tile(&model->tower, &model->tower.tiles[28], 225, 41 + (15 * 9));
    initialize_tile(&model->tower, &model->tower.tiles[29], 225 + (15 * 4), 41 + (15 * 9));
    initialize_tile(&model->tower, &model->tower.tiles[30], 225 + (15 * 5), 41 + (15 * 9));
    initialize_tile(&model->tower, &model->tower.tiles[31], 225 + (15 * 9), 41 + (15 * 9));
    /*Row 11*/
    initialize_tile(&model->tower, &model->tower.tiles[32], 225 + 15, 41 + (15 * 10));
    initialize_tile(&model->tower, &model->tower.tiles[33], 225 + (15 * 4), 41 + (15 * 10));
    initialize_tile(&model->tower, &model->tower.tiles[34], 225 + (15 * 5), 41 + (15 * 10));
    initialize_tile(&model->tower, &model->tower.tiles[35], 225 + (15 * 8), 41 + (15 * 10));
    /*Row 12*/
    initialize_tile(&model->tower, &model->tower.tiles[36], 225 + (15 * 2), 41 + (15 * 11));
    initialize_tile(&model->tower, &model->tower.tiles[37], 225 + (15 * 3), 41 + (15 * 11));
    initialize_tile(&model->tower, &model->tower.tiles[38], 225 + (15 * 4), 41 + (15 * 11));
    initialize_tile(&model->tower, &model->tower.tiles[39], 225 + (15 * 5), 41 + (15 * 11));
    initialize_tile(&model->tower, &model->tower.tiles[40], 225 + (15 * 6), 41 + (15 * 11));
    initialize_tile(&model->tower, &model->tower.tiles[41], 225 + (15 * 7), 41 + (15 * 11));
    /*Row 13*/
    initialize_tile(&model->tower, &model->tower.tiles[42], 225, 41 + (15 * 12));
    initialize_tile(&model->tower, &model->tower.tiles[43], 225 + (15 * 2), 41 + (15 * 12));
    initialize_tile(&model->tower, &model->tower.tiles[44], 225 + (15 * 7), 41 + (15 * 12));
    initialize_tile(&model->tower, &model->tower.tiles[45], 225 + (15 * 9), 41 + (15 * 12));
    /*Row 14*/
    initialize_tile(&model->tower, &model->tower.tiles[46], 225 + 15, 41 + (15 * 13));
    initialize_tile(&model->tower, &model->tower.tiles[47], 225 + (15 * 2), 41 + (15 * 13));
    initialize_tile(&model->tower, &model->tower.tiles[48], 225 + (15 * 4), 41 + (15 * 13));
    initialize_tile(&model->tower, &model->tower.tiles[49], 225 + (15 * 5), 41 + (15 * 13));
    initialize_tile(&model->tower, &model->tower.tiles[50], 225 + (15 * 7), 41 + (15 * 13));
    initialize_tile(&model->tower, &model->tower.tiles[51], 225 + (15 * 8), 41 + (15 * 13));
    /*Row 15*/
    initialize_tile(&model->tower, &model->tower.tiles[52], 225 + (15 * 2), 41 + (15 * 14));
    initialize_tile(&model->tower, &model->tower.tiles[53], 225 + (15 * 3), 41 + (15 * 14));
    initialize_tile(&model->tower, &model->tower.tiles[54], 225 + (15 * 6), 41 + (15 * 14));
    initialize_tile(&model->tower, &model->tower.tiles[55], 225 + (15 * 7), 41 + (15 * 14));
    /*Row 16*/
    initialize_tile(&model->tower, &model->tower.tiles[56], 225, 41 + (15 * 15));
    initialize_tile(&model->tower, &model->tower.tiles[57], 225 + 15, 41 + (15 * 15));
    initialize_tile(&model->tower, &model->tower.tiles[58], 225 + (15 * 2), 41 + (15 * 15));
    initialize_tile(&model->tower, &model->tower.tiles[59], 225 + (15 * 7), 41 + (15 * 15));
    initialize_tile(&model->tower, &model->tower.tiles[60], 225 + (15 * 8), 41 + (15 * 15));
    initialize_tile(&model->tower, &model->tower.tiles[61], 225 + (15 * 9), 41 + (15 * 15));
    /*Row 17*/
    initialize_tile(&model->tower, &model->tower.tiles[62], 225 + 15, 41 + (15 * 16));
    initialize_tile(&model->tower, &model->tower.tiles[63], 225 + (15 * 3), 41 + (15 * 16));
    initialize_tile(&model->tower, &model->tower.tiles[64], 225 + (15 * 6), 41 + (15 * 16));
    initialize_tile(&model->tower, &model->tower.tiles[65], 225 + (15 * 8), 41 + (15 * 16));
    /*Row 18*/
    initialize_tile(&model->tower, &model->tower.tiles[66], 225, 41 + (15 * 17));
    initialize_tile(&model->tower, &model->tower.tiles[67], 225 + (15 * 4), 41 + (15 * 17));
    initialize_tile(&model->tower, &model->tower.tiles[68], 225 + (15 * 5), 41 + (15 * 17));
    initialize_tile(&model->tower, &model->tower.tiles[69], 225 + (15 * 9), 41 + (15 * 17));
    /*Row 19*/
    initialize_tile(&model->tower, &model->tower.tiles[70], 225 + (15 * 2), 41 + (15 * 18));
    initialize_tile(&model->tower, &model->tower.tiles[71], 225 + (15 * 3), 41 + (15 * 18));
    initialize_tile(&model->tower, &model->tower.tiles[72], 225 + (15 * 6), 41 + (15 * 18));
    initialize_tile(&model->tower, &model->tower.tiles[73], 225 + (15 * 7), 41 + (15 * 18));
    /*Row 20*/
    initialize_tile(&model->tower, &model->tower.tiles[74], 225 + 15, 41 + (15 * 19));
    initialize_tile(&model->tower, &model->tower.tiles[75], 225 + (15 * 4), 41 + (15 * 19));
    initialize_tile(&model->tower, &model->tower.tiles[76], 225 + (15 * 5), 41 + (15 * 19));
    initialize_tile(&model->tower, &model->tower.tiles[77], 225 + (15 * 8), 41 + (15 * 19));
}
