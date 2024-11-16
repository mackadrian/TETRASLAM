/**
 * @file EVENTS.C
 * @brief contains all of TETRASLAM's event functions.
 * @author Mack Bautista
 */

#include "events.h"
#include <stdio.h>

/*
----- FUNCTION: move_player_piece -----
Purpose: moves the player's active piece left or right

Parameters: Tetromino active_piece       active piece address
            Field playing_field          playing_field address
            Tower tower                  tower address
            Direction direction          LEFT or RIGHT directions
Limitations: - Model needs to be initialized first otherwise this doesn't work.
*/
void move_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower, Direction direction)
{
    unsigned int curr_x = active_piece->x;

    update_active_piece(active_piece, direction);

    if (tower_collision(active_piece, tower))
    {
        active_piece->x = curr_x;
        return;
    }

    if (player_bounds_collision(active_piece, playing_field))
    {
        active_piece->x = curr_x;
        return;
    }
}

/*
----- FUNCTION: drop_active_piece -----
Purpose: drops the active piece in the playing field

Parameters: Tetromino active_piece      active piece address
            Tetromino playing_field     playing field address
            Tower tower                 tower address

Limitations: - Model needs to be initialized with the proper active_piece, playing_field, and tower properties.
*/
void drop_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower)
{
    active_piece->dropped = TRUE;

    update_active_piece(active_piece, DROP);

    if (tower_collision(active_piece, tower))
    {
        active_piece->y -= active_piece->velocity_y;
        active_piece->dropped = FALSE;
        active_piece->merged = TRUE;
    }

    if (player_bounds_collision(active_piece, playing_field))
    {
        active_piece->y -= active_piece->velocity_y;
        active_piece->dropped = FALSE;
        active_piece->merged = TRUE;
    }
}

/*
----- FUNCTION: reset_active_piece -----
Purpose: resets the player's position to the top centre of the playing field after merging
         with the tower.

Parameters: Tetromino player    tetromino address
            Tetromino pieces[]  player_pieces address
            Field playing_field playing_field address
            Tower tower         tower address

Limitations: - Resets the active piece to the original starting position.
*/
void reset_active_piece(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower)
{
    int reload_index = active_piece->curr_index;
    update_tower(active_piece, tower);

    *active_piece = pieces[reload_index];
    active_piece->curr_index = reload_index;
}

/*
----- FUNCTION: cycle_active_piece -----
Purpose: cycles the active piece to the next piece.

Parameters: Tetromino active_piece  active_piece address
            Tetromino pieces[]      all of the 7 pieces address
            Field playing_field     playing_field address
            Tower tower             tower address

Limitations: - Model needs to be initialized with active_piece, pieces array, and playing_field properties.
*/
void cycle_active_piece(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower)
{
    const int(*layout)[PIECE_SIZE] = NULL;
    unsigned int prev_x = active_piece->x;
    unsigned int prev_y = active_piece->y;
    int next_index = (active_piece->curr_index + 1) % 7;

    *active_piece = pieces[next_index];
    active_piece->curr_index = next_index;
    active_piece->x = prev_x;
    active_piece->y = prev_y;

    layout = cycle_piece_layout(active_piece->curr_index);
    if (layout == NULL)
    {
        return;
    }

    active_piece->layout = layout;

    if (player_bounds_collision(active_piece, playing_field))
    {
        active_piece->x -= active_piece->velocity_x;
        return;
    }

    if (tower_collision(active_piece, tower))
    {
        while (tower_collision(active_piece, tower))
        {
            active_piece->x -= active_piece->velocity_x;
        }
        return;
    }
}

/*
----- FUNCTION: clear_completed_rows -----
Purpose: clears the completed rows where the column is full

Parameters: Tower tower     tower address

Limitations: - Model needs to be initialized with active_piece, pieces array, and playing_field properties.
*/
void clear_completed_rows(Tower *tower, Tetromino *active_piece)
{
    int row, col;

    while (check_row_clearance(tower, active_piece))
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            tower->grid[tower->max_row][col] = 0;
        }
        tower->max_row--;
    }
}