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
bool process_events(Model *model, char *input);
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
int main()
{
    Model model;
    UINT32 time_then, time_now, time_elapsed;
    UINT32 *frame_buffer = Physbase();

    char ch = KEY_NULL;
    bool user_quit = FALSE;
    bool game_ended = FALSE;

    clear_screen(frame_buffer);
    init_starting_model(&model);

    render(&model, frame_buffer, (UINT16 *)frame_buffer, (UINT8 *)frame_buffer);

    time_then = get_time();

    while (!user_quit)
    {
        user_input(&ch);

        time_now = get_time();
        time_elapsed = time_now - time_then;

        if (time_elapsed > 1)
        {
            exit_request(&ch, &user_quit);
            game_ended = process_events(&model, &ch);
            if (game_ended)
            {
                break;
            }

            clear_screen(frame_buffer);
            render(&model, frame_buffer, (UINT16 *)frame_buffer, (UINT8 *)frame_buffer);
            time_then = time_now;
        }
    }

    return 0;
}

/*
----- FUNCTION: process_events -----
Purpose:
    - Processes the synchronized events to update the model and check for collision or win conditions.

Details:
    - Checks if the active piece has merged with the tower, resets the active piece, clears completed rows, and updates the counter.
    - Checks if a tower collision or win condition is met and returns a flag to indicate whether the game should end.

Parameters:
    - RequestQueue *queue: Pointer to the queue containing the player's requests.
    - Model *model: Pointer to the game model that holds the tower state and other necessary data.
*/
bool process_events(Model *model, char *input)
{
    bool game_ended = FALSE;

    if (input != KEY_NULL)
    {
        handle_requests(model, input);
    }

    if (model->tower.is_row_full > 0)
    {
        clear_completed_rows(&model->tower);
    }

    update_counter(&model->counter, &model->tower);

    if (fatal_tower_collision(&model->tower) || win_condition(&model->tower))
    {
        game_ended = TRUE;
    }

    return game_ended;
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
    initialize_tower(&model->tower, &level_1);
    initialize_counter(&model->counter, &model->tower, 224 + 160 + 16, 32);

    initialize_tetromino(&model->player_pieces[0], 288, 32, 16, 64, I_PIECE);
    initialize_tetromino(&model->player_pieces[1], 288, 32, 32, 46, J_PIECE);
    initialize_tetromino(&model->player_pieces[2], 288, 32, 32, 46, L_PIECE);
    initialize_tetromino(&model->player_pieces[3], 288, 32, 32, 32, O_PIECE);
    initialize_tetromino(&model->player_pieces[4], 288, 32, 48, 32, S_PIECE);
    initialize_tetromino(&model->player_pieces[5], 288, 32, 48, 32, T_PIECE);
    initialize_tetromino(&model->player_pieces[6], 288, 32, 48, 32, Z_PIECE);
}
