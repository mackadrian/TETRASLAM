/**
 * @file EVENTS.C
 * @brief contains all of TETRASLAM's event functions.
 * @author Mack Bautista
 */

#include "events.h"
#include <stdio.h>

/*
----- FUNCTION: move_left_request -----
Purpose:
    - Initiates a request to move the active piece to the left.

Details:
    - Calls the function to update the position of the active piece.
    - Performs collision checks with the tower and boundaries.
    - Cancels the move if a collision is detected.

Parameters:
    - Tetromino *active_piece: Pointer to the current active piece.
    - Field *playing_field: Pointer to the game field (for boundary checks).
    - Tower *tower: Pointer to the tower (for collision checks).
*/
void move_left_request(Tetromino *active_piece, Field *playing_field, Tower *tower)
{
    unsigned int curr_x = active_piece->x;
    move_active_piece_left(active_piece);

    if (tower_collision(active_piece, tower, playing_field))
    {
        active_piece->x = curr_x;
    }

    if (player_bounds_collision(active_piece, playing_field))
    {
        active_piece->x = curr_x;
    }
}

/*
----- FUNCTION: move_right_request -----
Purpose:
    - Initiates a request to move the active piece to the right.

Details:
    - Calls the function to update the position of the active piece.
    - Performs collision checks with the tower and boundaries.
    - Cancels the move if a collision is detected.

Parameters:
    - Tetromino *active_piece: Pointer to the current active piece.
    - Field *playing_field: Pointer to the game field (for boundary checks).
    - Tower *tower: Pointer to the tower (for collision checks).
*/
void move_right_request(Tetromino *active_piece, Field *playing_field, Tower *tower)
{
    unsigned int curr_x = active_piece->x;
    move_active_piece_right(active_piece);

    if (tower_collision(active_piece, tower, playing_field))
    {
        active_piece->x = curr_x;
    }

    if (player_bounds_collision(active_piece, playing_field))
    {
        active_piece->x = curr_x;
    }
}

/*
----- FUNCTION: drop_request -----
Purpose:
    - Initiates a request to drop the active piece down to the next valid position.

Details:
    - Calls the function to update the position of the active piece.
    - Performs collision checks with the tower and boundaries.
    - Continues to drop the piece until a collision is detected.
    - Sets the active_piece->dropped status appropriately.

Parameters:
    - Tetromino *active_piece: Pointer to the current active piece.
    - Field *playing_field: Pointer to the game field (for boundary checks).
    - Tower *tower: Pointer to the tower (for collision checks).
*/
void drop_request(Tetromino *active_piece, Field *playing_field, Tower *tower)
{
    active_piece->dropped = TRUE;

    while (active_piece->dropped)
    {
        drop_active_piece(active_piece);

        if (tower_collision(active_piece, tower, playing_field))
        {
            active_piece->y -= active_piece->velocity_y;
            active_piece->dropped = FALSE;
            active_piece->merged = TRUE;
            update_tower(playing_field, active_piece, tower);
        }

        if (player_bounds_collision(active_piece, playing_field))
        {
            active_piece->y -= active_piece->velocity_y;
            active_piece->dropped = FALSE;
            active_piece->merged = TRUE;
            update_tower(playing_field, active_piece, tower);
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
    - Tetromino player_pieces[]:       Array of Tetromino structures representing all available player_pieces.
    - Field *playing_field:     Pointer to the playing field structure.
    - Tower *tower:             Pointer to the tower structure.

Limitations:
    - The active piece is reset to its original starting position with no consideration
      for custom starting positions.
*/
void reset_active_piece(Tetromino *active_piece, Tetromino player_pieces[], Field *playing_field, Tower *tower)
{
    Tetromino shifted_left, shifted_right;
    int reload_index;
    if (fatal_tower_collision(tower))
    {
        return;
    }

    reload_index = active_piece->curr_index;
    *active_piece = player_pieces[reload_index];
    active_piece->curr_index = reload_index;

    if (!tower_collision(active_piece, tower, playing_field))
    {
        return;
    }

    shifted_right = *active_piece;
    shifted_right.x += shifted_right.velocity_x;

    if (!tower_collision(&shifted_right, tower, playing_field))
    {
        *active_piece = shifted_right;
        return;
    }

    shifted_left = *active_piece;
    shifted_left.x -= shifted_left.velocity_x;

    if (!tower_collision(&shifted_left, tower, playing_field))
    {
        *active_piece = shifted_left;
        return;
    }
}

/*
----- FUNCTION: cycle_active_piece -----
Purpose:
    - Cycles the active piece to the next piece in the sequence.

Details:
    - Swaps the active piece with the next piece in the predefined array of player_pieces.
    - Adjusts the new piece's position to prevent boundary or tower collisions.
    - If unable to resolve collisions, the piece is reset to its default position.

Parameters:
    - Tetromino *active_piece:  Pointer to the active piece structure.
    - Tetromino player_pieces[]: Array of Tetromino structures representing all available player_pieces.
    - Field *playing_field:     Pointer to the playing field structure.
    - Tower *tower:             Pointer to the tower structure.

Limitations:
    - Requires initialized active_piece, player_pieces array, and playing_field structures.
*/
void cycle_active_piece(Tetromino *active_piece, Tetromino player_pieces[], Field *playing_field, Tower *tower)
{
    unsigned int prev_x = active_piece->x;
    unsigned int prev_y = active_piece->y;

    int next_index = (active_piece->curr_index + 1) % 7;
    *active_piece = player_pieces[next_index];
    active_piece->curr_index = next_index;

    active_piece->x = prev_x;
    active_piece->y = prev_y;

    active_piece->layout = cycle_piece_layout(active_piece->curr_index);

    if (player_bounds_collision(active_piece, playing_field) || tower_collision(active_piece, tower, playing_field))
    {
        active_piece->x = (playing_field->width >> 1) + (playing_field->x - active_piece->velocity_x);
        active_piece->y = playing_field->y;
    }
}

/*
----- FUNCTION: clear_completed_rows -----
Purpose:
    - Clears any fully occupied rows in the tower and shifts rows above downward
      until a collision or the top of the grid is reached.

Details:
    - Scans the tower grid from the bottom to the top of the active piece's starting position.
    - Identifies full rows, clears them, and shifts rows above downward.
    - Updates the tower's tile positions and count to match the modified grid.

Parameters:
    - Field *playing_field: Pointer to the playing field structure (unused here).
    - Tower *tower:         Pointer to the tower structure.
    - Tetromino *active_piece: Pointer to the active piece structure.

Limitations:
    - Assumes proper initialization of the tower structure and its grid.
    - Does not handle game-over scenarios where the top row is filled.

*/
void clear_completed_rows(Tower *tower, Tetromino *active_piece)
{
    int row, col;

    while (tower->is_row_full > 0)
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
        tower->is_row_full--;
        tower->max_row--;
        check_rows(tower, active_piece);
    }
}
