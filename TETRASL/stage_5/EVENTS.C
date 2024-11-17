/**
 * @file EVENTS.C
 * @brief contains all of TETRASLAM's event functions.
 * @author Mack Bautista
 */

#include "events.h"
#include <stdio.h>

/*
----- FUNCTION: move_active_piece -----
Purpose:
    - Moves the player's active piece left or right.

Details:
    - Updates the active piece's x-coordinate based on the given direction.
    - Checks for collisions with the tower and playing field boundaries,
    - and reverts the movement if a collision occurs.

Parameters:
    - Tetromino *active_piece:  Pointer to the active piece structure.
    - Field *playing_field:     Pointer to the playing field structure.
    - Tower *tower:             Pointer to the tower structure.
    - Direction direction:      Direction of movement (LEFT or RIGHT).

Limitations:
    - The model needs to be initialized first; otherwise, the function does not work.
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
Purpose:
    - Drops the active piece in the playing field.

Details:
    - Moves the active piece downward until it either collides with the
      tower or reaches the playing field boundary. Upon collision, the pieces
      merged into the tower and its position is finalized.

Parameters:
    - Tetromino *active_piece:  Pointer to the active piece structure.
    - Field *playing_field:     Pointer to the playing field structure.
    - Tower *tower:             Pointer to the tower structure.

Limitations:
    - The model must be properly initialized with valid active_piece, playing_field,
      and tower structures before calling this function.
*/
void drop_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower)
{
    active_piece->dropped = TRUE;

    while (active_piece->dropped)
    {
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
}

/*
----- FUNCTION: reset_active_piece -----
Purpose:
    - Resets the active piece's position to the top center of the playing field.

Details:
    - After merging the current active piece into the tower, this function
      resets the active piece to its initial state for the next round.

Parameters:
    - Tetromino *active_piece:  Pointer to the active piece structure.
    - Tetromino pieces[]:       Array of Tetromino structures representing all available pieces.
    - Field *playing_field:     Pointer to the playing field structure.
    - Tower *tower:             Pointer to the tower structure.

Limitations:
    - The active piece is reset to its original starting position with no consideration
      for custom starting positions.
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
Purpose:
    - Cycles the active piece to the next piece in the sequence.

Details:
    - Swaps the active piece with the next piece in the predefined array of pieces.
    - Adjusts the new piece's position to prevent boundary or tower collisions.

Parameters:
    - Tetromino *active_piece:  Pointer to the active piece structure.
    - Tetromino pieces[]:         Array of Tetromino structures representing all available pieces.
    - Field *playing_field:       Pointer to the playing field structure.
    - Tower *tower:               Pointer to the tower structure.

Limitations:
    - Requires initialized active_piece, pieces array, and playing_field structures.
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

    while (player_bounds_collision(active_piece, playing_field) || tower_collision(active_piece, tower))
    {
        adjust_position(active_piece, playing_field);

        if (active_piece->y + active_piece->height > playing_field->y + playing_field->height)
        {
            adjust_position(active_piece, playing_field);
        }
        else
        {
            break;
        }
    }
}

/*
----- FUNCTION: adjust_position -----
Purpose:
    - Adjusts the active piece's position to resolve collisions.

Details:
    - Moves the active piece within the boundaries of the playing field
      if it collides with the tower or exceeds the playing field boundaries.

Parameters:
    - Tetromino *active_piece:  Pointer to the active piece structure.
    - Field *playing_field:     Pointer to the playing field structure.

Limitations:
    - Only resolves collisions caused by out-of-bounds conditions.
*/
void adjust_position(Tetromino *active_piece, Field *playing_field)
{
    if (active_piece->x + active_piece->width > playing_field->x + playing_field->width)
    {
        active_piece->x -= active_piece->velocity_x;
    }
    else if (active_piece->x < playing_field->x)
    {
        active_piece->x += active_piece->velocity_x;
    }
}

/*
----- FUNCTION: clear_completed_rows -----
Purpose:
    - Clears any rows in the tower that are completely filled with tiles.

Details:
    - Iterates through the tower's rows, identifies full rows, removes the
      corresponding tiles, and shifts remaining rows downward.

Parameters:
    - Tower *tower:             Pointer to the tower structure.
    - Tetromino *active_piece:  Pointer to the active piece structure.

Limitations:
    - Requires proper initialization of the tower structure.
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

        for (row = tower->max_row - 1; row >= 0; row--)
        {
            for (col = 0; col < GRID_WIDTH; col++)
            {
                tower->grid[row + 1][col] = tower->grid[row][col];
            }
        }

        tower->max_row--;

        update_tiles(tower);
    }
}