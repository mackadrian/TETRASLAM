/**
 * @file T_RENDER.C
 * @brief tests how each model and bitmaps are rendered to the screen.
 * @author Mack Bautista
 */

#include "events.h"
#include "render.h"
#include <osbind.h>
#include <stdio.h>

void snapshot_1();
void snapshot_2();
void snapshot_3();

int test_layout_1[GRID_HEIGHT][GRID_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {0, 1, 1, 0, 1, 1, 0, 1, 1, 0},
    {0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
    {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0}};

int test_layout_2[GRID_HEIGHT][GRID_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 0, 1, 0, 0, 1, 0, 1, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 1, 0, 0, 1, 0, 1, 1},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};

int test_layout_3[GRID_HEIGHT][GRID_WIDTH] = {
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0, 1, 0},
    {0, 1, 1, 0, 1, 1, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 1, 1, 0},
    {1, 1, 0, 1, 0, 1, 1, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 1, 1, 1, 0, 1, 0},
    {1, 1, 0, 1, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 1, 1, 1, 0},
    {0, 1, 0, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 0, 0, 1, 1},
    {0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 1, 0, 0, 1, 1, 0},
    {1, 0, 1, 1, 0, 1, 0, 1, 0, 0},
    {1, 0, 0, 1, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 1, 0, 0}};

/*
----- FUNCTION: main -----
Purpose:
    - The entry point of the program.
    - Calls snapshot_1() and snapshot_2() functions to render and display different game snapshots.
Details:
    - The main function executes the game setup and rendering for two snapshots.
    - `snapshot_1()` initializes the model and game field, sets up the active piece and tower, then renders the game state.
    - `snapshot_2()` (not yet implemented) will likely set up another variation of the game state for testing or rendering purposes.
    - After the snapshots are rendered, the function returns with an exit status of 0.
*/
int main()
{
    snapshot_1();
    snapshot_2();
    snapshot_3();

    return 0;
}

/*
----- FUNCTION: snapshot_1 -----
Purpose:
    - Captures a specific state of the game, rendering the initial layout of the playing field, the tower,
      and the active tetrominoes, followed by rendering the game to the screen.

Details:
    - Initializes the playing field, tower, and player pieces.
    - Renders the scene to the screen buffer and clears the screen.

Parameters:
    - None.

Limitations:
    - Assumes proper initialization of global variables and game data structures.

*/
void snapshot_1()
{
    Model create_model;
    Model *model = &create_model;
    UINT32 *base_32 = (UINT32 *)Physbase();
    UINT16 *base_16 = (UINT16 *)Physbase();
    UINT8 *base_8 = (UINT8 *)Physbase();
    clear_screen(base_32);

    initialize_tetromino(&model->active_piece, 288, 32, 16, 64, I_PIECE);
    initialize_field(&model->playing_field, 224, 32, 160, 320);
    initialize_tower(&model->tower, &test_layout_1);
    initialize_counter(&model->counter, &model->tower, 224 + 160 + 16, 32);

    initialize_tetromino(&model->player_pieces[0], 288, 32, 16, 64, I_PIECE);
    initialize_tetromino(&model->player_pieces[1], 288, 32, 32, 46, J_PIECE);
    initialize_tetromino(&model->player_pieces[2], 288, 32, 32, 46, L_PIECE);
    initialize_tetromino(&model->player_pieces[3], 288, 32, 32, 32, O_PIECE);
    initialize_tetromino(&model->player_pieces[4], 288, 32, 48, 32, S_PIECE);
    initialize_tetromino(&model->player_pieces[5], 288, 32, 48, 32, T_PIECE);
    initialize_tetromino(&model->player_pieces[6], 288, 32, 48, 32, Z_PIECE);

    render(model, base_32, base_16, base_8);
    Cnecin();
    clear_screen(base_32);
}

/*
----- FUNCTION: snapshot_2 -----
Purpose:
    - Captures a different state of the game with an altered tower layout and different pieces initialized.

Details:
    - This snapshot uses a different tower layout (`test_layout_2`).
    - Tetrominoes are positioned and initialized differently.

Parameters:
    - None.

Limitations:
    - Assumes proper initialization of global variables and game data structures.

*/
void snapshot_2()
{
    Model create_model;
    Model *model = &create_model;
    UINT32 *base_32 = (UINT32 *)Physbase();
    UINT16 *base_16 = (UINT16 *)Physbase();
    UINT8 *base_8 = (UINT8 *)Physbase();
    clear_screen(base_32);

    initialize_tetromino(&model->active_piece, 288, 32, 16, 64, J_PIECE);
    initialize_field(&model->playing_field, 224, 32, 160, 320);
    initialize_tower(&model->tower, &test_layout_2);
    initialize_counter(&model->counter, &model->tower, 224 + 160 + 16, 32);

    initialize_tetromino(&model->player_pieces[0], 288, 32, 16, 64, L_PIECE);
    initialize_tetromino(&model->player_pieces[1], 288, 32, 32, 46, Z_PIECE);
    initialize_tetromino(&model->player_pieces[2], 288, 32, 32, 46, T_PIECE);
    initialize_tetromino(&model->player_pieces[3], 288, 32, 32, 32, I_PIECE);
    initialize_tetromino(&model->player_pieces[4], 288, 32, 48, 32, S_PIECE);
    initialize_tetromino(&model->player_pieces[5], 288, 32, 48, 32, J_PIECE);
    initialize_tetromino(&model->player_pieces[6], 288, 32, 48, 32, O_PIECE);

    render(model, base_32, base_16, base_8);
    Cnecin();
    clear_screen(base_32);
}

void snapshot_3()
{
    Model create_model;
    Model *model = &create_model;
    UINT32 *base_32 = (UINT32 *)Physbase();
    UINT16 *base_16 = (UINT16 *)Physbase();
    UINT8 *base_8 = (UINT8 *)Physbase();
    clear_screen(base_32);

    initialize_tetromino(&model->active_piece, 288, 32, 16, 64, J_PIECE);
    initialize_field(&model->playing_field, 224, 32, 160, 320);
    initialize_tower(&model->tower, &test_layout_3);
    initialize_counter(&model->counter, &model->tower, 224 + 160 + 16, 32);

    initialize_tetromino(&model->player_pieces[0], 288, 32, 16, 64, L_PIECE);
    initialize_tetromino(&model->player_pieces[1], 288, 32, 32, 46, Z_PIECE);
    initialize_tetromino(&model->player_pieces[2], 288, 32, 32, 46, T_PIECE);
    initialize_tetromino(&model->player_pieces[3], 288, 32, 32, 32, I_PIECE);
    initialize_tetromino(&model->player_pieces[4], 288, 32, 48, 32, S_PIECE);
    initialize_tetromino(&model->player_pieces[5], 288, 32, 48, 32, J_PIECE);
    initialize_tetromino(&model->player_pieces[6], 288, 32, 48, 32, O_PIECE);

    render(model, base_32, base_16, base_8);
    Cnecin();
    clear_screen(base_32);
}
