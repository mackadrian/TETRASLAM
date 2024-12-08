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
#include "music.h"
#include "effects.h"
#include <osbind.h>

void init_starting_model(Model *model);
bool process_events(Model *model, char *input);
void set_buffers(UINT32 **back_buffer, UINT32 **front_buffer, UINT32 *orig_buffer, UINT8 back_buffer_array[]);

UINT32 get_time();
UINT8 allocated_buffer[32260];

/*
----- FUNCTION: main -----
Purpose:
    - Main game loop of TETRASLAM.

Details:
    - The function starts the game, initializing the game model, rendering the screen, and processing user inputs.
    - It contains a loop that listens for keypresses, processes the game events asynchronously and synchronously,
      and updates the screen accordingly. The game will continue until the user chooses to quit (presses ESC).
*/
int main()
{
    Model model;
    UINT32 time_then, time_now, time_elapsed;
    UINT32 *front_buffer, *back_buffer;
    UINT32 *original_buffer = (UINT32 *)Physbase();

    char ch = KEY_NULL;
    bool user_quit = FALSE;
    bool is_curr_front_buffer = TRUE;
    bool needs_render = TRUE;
    bool game_ended = FALSE;

    init_starting_model(&model);
    start_music();

    time_then = get_time();
    set_buffers(&back_buffer, &front_buffer, original_buffer, allocated_buffer);

    while (!user_quit)
    {
        user_input(&ch); /*create asynchronous requests*/

        time_now = get_time();
        time_elapsed = time_now - time_then;

        if (time_elapsed > 1)
        {
            /*processing requests*/
            exit_request(&ch, &user_quit);
            game_ended = process_events(&model, &ch);

            if (game_ended)
            {
                break;
            }

            needs_render = TRUE;

            if (needs_render)
            {
                if (is_curr_front_buffer)
                {
                    render(&model, back_buffer, (UINT16 *)back_buffer, (UINT8 *)back_buffer);
                    Setscreen(-1, back_buffer, -1);
                    Vsync();
                    clear_screen(front_buffer);
                    is_curr_front_buffer = FALSE;
                }
                else
                {
                    render(&model, front_buffer, (UINT16 *)front_buffer, (UINT8 *)front_buffer);
                    Setscreen(-1, front_buffer, -1);
                    Vsync();
                    clear_screen(back_buffer);
                    is_curr_front_buffer = TRUE;
                }

                needs_render = FALSE;
            }

            update_music(time_elapsed);
            time_then = time_now;
        }
    }

    Setscreen(-1, original_buffer, -1);
    Vsync();

    return 0;
}

/*
----- FUNCTION: set_buffers -----
Purpose:
    - Initializes the back and front buffer pointers for double buffering.

Details:
    - Aligns the back buffer pointer to the nearest 256-byte boundary within the provided back_buffer_array.
    - Sets the front buffer pointer to point to the original buffer.

Parameters:
    - back_buffer (UINT32**): Pointer to the back buffer pointer to be initialized.
    - front_buffer (UINT32**): Pointer to the front buffer pointer to be initialized.
    - orig_buffer (UINT32*): Pointer to the original buffer.
    - back_buffer_array (UINT8[]): Array used for alignment and back buffer initialization.

Return:
    - Modifies the back buffer pointer to a 256-byte aligned address within back_buffer_array.
    - Updates the front buffer pointer to point to orig_buffer.
*/
void set_buffers(UINT32 **back_buffer, UINT32 **front_buffer, UINT32 *orig_buffer, UINT8 back_buffer_array[])
{
    UINT32 address = (UINT32)back_buffer_array;
    address = (address + 0xFF) & ~0xFF;
    *back_buffer = (UINT32 *)address;

    *front_buffer = orig_buffer;
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
        play_clear_row_sound();
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
