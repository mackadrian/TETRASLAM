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
        move_left_request(&model->active_piece, &model->playing_field, &model->tower);
        break;
    case KEY_UPPER_M:
    case KEY_LOWER_M:
        move_right_request(&model->active_piece, &model->playing_field, &model->tower);
        break;
    case KEY_SPACE:
        drop_request(&model->active_piece, &model->playing_field, &model->tower);
        break;
    case KEY_UPPER_C:
    case KEY_LOWER_C:
        cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
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
        update_tower(&model->playing_field, &model->active_piece, &model->tower);
        update_tiles(&model->playing_field, &model->tower, &model->active_piece);
        clear_completed_rows(&model->playing_field, &model->tower, &model->active_piece);
        reset_active_piece(&model->active_piece, model->player_pieces, &model->playing_field, &model->tower);
    }

    update_counter(&model->counter, &model->tower);
}

/*
----- FUNCTION: get_time -----
P. Pospisil, "get_time function," lab material, COMP2659 Computing Machinery II , Mount Royal University, Nov. 2024.
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
    initialize_tetromino(&model->active_piece, 288, 32, 16, 64, I_PIECE);
    initialize_field(&model->playing_field, 224, 32, 160, 320);
    initialize_tower(&model->playing_field, &model->tower, 78);
    initialize_counter(&model->counter, &model->tower, 224 + 160 + 16, 32);

    initialize_tetromino(&model->player_pieces[0], 288, 32, 16, 64, I_PIECE);
    initialize_tetromino(&model->player_pieces[1], 288, 32, 32, 46, J_PIECE);
    initialize_tetromino(&model->player_pieces[2], 288, 32, 32, 46, L_PIECE);
    initialize_tetromino(&model->player_pieces[3], 288, 32, 32, 32, O_PIECE);
    initialize_tetromino(&model->player_pieces[4], 288, 32, 48, 32, S_PIECE);
    initialize_tetromino(&model->player_pieces[5], 288, 32, 48, 32, T_PIECE);
    initialize_tetromino(&model->player_pieces[6], 288, 32, 48, 32, Z_PIECE);

    /*Plotting tiles */
    /*Row 4*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[0], 224, 32 + (16 * 3));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[1], 224 + (16 * 9), 32 + (16 * 3));
    /*Row 5*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[2], 224, 32 + (16 * 4));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[3], 224 + (16 * 2), 32 + (16 * 4));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[4], 224 + (16 * 3), 32 + (16 * 4));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[5], 224 + (16 * 6), 32 + (16 * 4));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[6], 224 + (16 * 7), 32 + (16 * 4));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[7], 224 + (16 * 9), 32 + (16 * 4));
    /*Row 6*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[8], 224 + (16 * 3), 32 + (16 * 5));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[9], 224 + (16 * 4), 32 + (16 * 5));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[10], 224 + (16 * 5), 32 + (16 * 5));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[11], 224 + (16 * 6), 32 + (16 * 5));
    /*Row 7*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[12], 224 + 16, 32 + (16 * 6));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[13], 224 + (16 * 8), 32 + (16 * 6));
    /*Row 8*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[14], 224, 32 + (16 * 7));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[15], 224 + (16 * 2), 32 + (16 * 7));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[16], 224 + (16 * 3), 32 + (16 * 7));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[17], 224 + (16 * 4), 32 + (16 * 7));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[18], 224 + (16 * 5), 32 + (16 * 7));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[19], 224 + (16 * 6), 32 + (16 * 7));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[20], 224 + (16 * 7), 32 + (16 * 7));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[21], 224 + (16 * 9), 32 + (16 * 7));
    /*Row 9*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[22], 224, 32 + (16 * 8));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[23], 224 + (16 * 2), 32 + (16 * 8));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[24], 224 + (16 * 3), 32 + (16 * 8));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[25], 224 + (16 * 6), 32 + (16 * 8));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[26], 224 + (16 * 7), 32 + (16 * 8));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[27], 224 + (16 * 9), 32 + (16 * 8));
    /*Row 10*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[28], 224, 32 + (16 * 9));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[29], 224 + (16 * 4), 32 + (16 * 9));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[30], 224 + (16 * 5), 32 + (16 * 9));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[31], 224 + (16 * 9), 32 + (16 * 9));
    /*Row 11*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[32], 224 + 16, 32 + (16 * 10));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[33], 224 + (16 * 4), 32 + (16 * 10));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[34], 224 + (16 * 5), 32 + (16 * 10));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[35], 224 + (16 * 8), 32 + (16 * 10));
    /*Row 12*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[36], 224 + (16 * 2), 32 + (16 * 11));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[37], 224 + (16 * 3), 32 + (16 * 11));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[38], 224 + (16 * 4), 32 + (16 * 11));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[39], 224 + (16 * 5), 32 + (16 * 11));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[40], 224 + (16 * 6), 32 + (16 * 11));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[41], 224 + (16 * 7), 32 + (16 * 11));
    /*Row 13*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[42], 224, 32 + (16 * 12));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[43], 224 + (16 * 2), 32 + (16 * 12));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[44], 224 + (16 * 7), 32 + (16 * 12));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[45], 224 + (16 * 9), 32 + (16 * 12));
    /*Row 14*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[46], 224 + 16, 32 + (16 * 13));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[47], 224 + (16 * 2), 32 + (16 * 13));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[48], 224 + (16 * 4), 32 + (16 * 13));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[49], 224 + (16 * 5), 32 + (16 * 13));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[50], 224 + (16 * 7), 32 + (16 * 13));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[51], 224 + (16 * 8), 32 + (16 * 13));
    /*Row 15*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[52], 224 + (16 * 2), 32 + (16 * 14));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[53], 224 + (16 * 3), 32 + (16 * 14));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[54], 224 + (16 * 6), 32 + (16 * 14));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[55], 224 + (16 * 7), 32 + (16 * 14));
    /*Row 16*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[56], 224, 32 + (16 * 15));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[57], 224 + 16, 32 + (16 * 15));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[58], 224 + (16 * 2), 32 + (16 * 15));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[59], 224 + (16 * 7), 32 + (16 * 15));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[60], 224 + (16 * 8), 32 + (16 * 15));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[61], 224 + (16 * 9), 32 + (16 * 15));
    /*Row 17*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[62], 224 + 16, 32 + (16 * 16));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[63], 224 + (16 * 3), 32 + (16 * 16));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[64], 224 + (16 * 6), 32 + (16 * 16));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[65], 224 + (16 * 8), 32 + (16 * 16));
    /*Row 18*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[66], 224, 32 + (16 * 17));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[67], 224 + (16 * 4), 32 + (16 * 17));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[68], 224 + (16 * 5), 32 + (16 * 17));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[69], 224 + (16 * 9), 32 + (16 * 17));
    /*Row 19*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[70], 224 + (16 * 2), 32 + (16 * 18));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[71], 224 + (16 * 3), 32 + (16 * 18));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[72], 224 + (16 * 6), 32 + (16 * 18));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[73], 224 + (16 * 7), 32 + (16 * 18));
    /*Row 20*/
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[74], 224 + 16, 32 + (16 * 19));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[75], 224 + (16 * 4), 32 + (16 * 19));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[76], 224 + (16 * 5), 32 + (16 * 19));
    initialize_tile(&model->playing_field, &model->tower, &model->tower.tiles[77], 224 + (16 * 8), 32 + (16 * 19));
}
