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

Parameters:
    - Tetromino *active_piece:  Pointer to the active piece structure.
    - Tetromino player_pieces[]:         Array of Tetromino structures representing all available player_pieces.
    - Field *playing_field:       Pointer to the playing field structure.
    - Tower *tower:               Pointer to the tower structure.

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

    while (player_bounds_collision(active_piece, playing_field) || (tower_collision(active_piece, tower, playing_field)))
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
void clear_completed_rows(Field *playing_field, Tower *tower, Tetromino *active_piece)
{
    unsigned int i, x, row, grid_x, grid_y;
    unsigned int full_row;

    get_grid_coordinates(playing_field, active_piece->x, active_piece->y, &grid_x, &grid_y);

    while (find_full_row(tower, &full_row))
    {
        for (i = full_row; i > 0; i--)
        {
            for (x = 0; x < GRID_WIDTH; x++)
            {
                tower->grid[i][x] = tower->grid[i - 1][x];
            }
        }

        for (x = 0; x < GRID_WIDTH; x++)
        {
            tower->grid[0][x] = 0;
        }
    }

    refresh_tower_tiles(tower, playing_field);
}

/*
----- FUNCTION: refresh_tower_tiles -----
Purpose:
    - Updates the 'tower->tiles' array to reflect the current state of the tower's grid.
    - Recalculates the positions of all tiles based on the updated grid after row-clearing or other changes.

Details:
    - Traverses the tower's grid from the top to 'tower->max_row'.
    - For every occupied cell in the grid (value 1), calculates its corresponding (x, y) position in pixels.
    - Updates the 'tower->tiles' array with the calculated positions.
    - Resets and updates the 'tower->tile_count' to match the number of occupied cells in the grid.

Parameters:
    - Tower *tower: Pointer to the tower structure.

Limitations:
    - Assumes that the 'tower->grid and 'tower->max_row' are correctly maintained.
    - Does not handle any logic related to row-clearing or active piece placement; this must be done beforehand.
*/
void refresh_tower_tiles(Tower *tower, Field *playing_field)
{
    unsigned int i, row, col, tile_y, tile_x;
    unsigned int tile_index = 0;

    for (row = 0; row <= tower->max_row; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            if (tower->grid[row][col] == 1)
            {
                tile_x = (col * CONST_VELOCITY) + playing_field->x;
                tile_y = (row * CONST_VELOCITY) + playing_field->y;

                initialize_tile(playing_field, tower, &tower->tiles[tile_index], tile_x, tile_y);

                tile_index++;
            }
        }
    }

    tower->tile_count = tile_index;
}

/*
----- FUNCTION: find_full_row -----
Purpose:
    - Finds the first full row in the tower's grid.
    - Iterates through the rows and checks if all columns in a row are filled (non-zero).
    - Returns the first full row found and updates the 'full_row' parameter.

Details:
    - The function loops through each row in the tower's grid.
    - For each row, it checks if every column is filled (i.e., non-zero).
    - If a full row is found, the row index is returned through the 'full_row' pointer.
    - If no full row is found after checking all rows, the function returns 'FALSE'.

Parameters:
    - Tower *tower: Pointer to the tower structure containing the grid.
    - unsigned int *full_row: Pointer to an unsigned int where the index of the first full row will be stored.

Return:
    - Returns 'TRUE' if a full row is found, and updates the 'full_row' parameter with the index of the full row.
    - Returns 'FALSE' if no full row is found in the grid.

Limitations:
    - Assumes that the tower's grid and 'tower->max_row' are correctly maintained.
    - Does not modify the grid; it only checks for full rows.
*/
bool find_full_row(Tower *tower, unsigned int *full_row)
{
    unsigned int row, x;

    for (row = 0; row < tower->max_row; row++)
    {
        bool is_full = TRUE;

        for (x = 0; x < GRID_WIDTH; x++)
        {
            if (tower->grid[row][x] == 0)
            {
                is_full = FALSE;
                break;
            }
        }

        if (is_full)
        {
            *full_row = row;
            return TRUE;
        }
    }

    return FALSE;
}
