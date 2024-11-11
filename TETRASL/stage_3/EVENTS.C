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
        printf("Tower collision detected. Reverting to x: %d\n", active_piece->x);
        return;
    }

    if (player_bounds_collision(active_piece, playing_field))
    {
        active_piece->x = curr_x;
        printf("Boundary collision detected. Reverting to x: %d\n", active_piece->x);
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

    while (active_piece->dropped)
    {
        update_active_piece(active_piece, DROP);

        if (tower_collision(active_piece, tower))
        {
            printf("Tower collision detected at y: %d\n", active_piece->y);
            active_piece->y -= active_piece->velocity_y;
            active_piece->dropped = FALSE;
            active_piece->merged = TRUE;
            printf("Reverting to y: %d\n", active_piece->y);
            return;
        }

        if (player_bounds_collision(active_piece, playing_field))
        {
            printf("Boundary collision detected at y: %d\n", active_piece->y);
            active_piece->y -= active_piece->velocity_y;
            active_piece->dropped = FALSE;
            active_piece->merged = TRUE;
            printf("Reverting to y: %d\n", active_piece->y);
            return;
        }
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

    if (fatal_tower_collision(tower, playing_field))
    {
        printf("GAME OVER... Collision at y: %u\n", active_piece->y);
    }

    *active_piece = pieces[reload_index];
    active_piece->curr_index = reload_index;

    printf("Loaded next active piece at x: %d, y: %d, width: %d, height: %d\n",
           active_piece->x, active_piece->y, active_piece->width, active_piece->height);
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

    printf("Cycling active piece. New piece index: %d, Previous position: x: %u, y: %u\n", next_index, prev_x, prev_y);

    layout = cycle_piece_layout(active_piece->curr_index);
    if (layout == NULL)
    {
        printf("Invalid piece layout.\n");
        return;
    }

    active_piece->layout = layout;

    if (player_bounds_collision(active_piece, playing_field))
    {
        active_piece->x -= active_piece->velocity_x;
        printf("Player bounds collision detected. Reverting to x: %d\n", active_piece->x);
        return;
    }

    if (tower_collision(active_piece, tower))
    {
        printf("Collision detected with the tower after cycling at x:%u, y:%u\n", active_piece->x, active_piece->y);
        while (tower_collision(active_piece, tower))
        {
            active_piece->x -= active_piece->velocity_x;
            printf("Adjusted active piece to avoid tower collision. New x: %u\n", active_piece->x);
        }
        return;
    }
}

/*
----- FUNCTION: clear_completed_row -----
Purpose: clears the row of the lowest tile position of the active piece if
            all tiles fill up the row at which it is merged in.

Parameters: Tetromino active_piece  active_piece address
            Tower tower             tower address

Limitations: - Model needs to be initialized with active_piece, pieces array, and playing_field properties.
*/
void clear_completed_row(Tetromino *active_piece, Tower *tower)
{
    unsigned int row, rows_to_check, lowest_row;

    rows_to_check = get_rows_to_check(active_piece);
    lowest_row = active_piece->y >> 4;
    printf("Checking for completed row starting from lowest_row: %u\n", lowest_row);

    for (row = lowest_row; row >= lowest_row - rows_to_check + 1; row--)
    {
        printf("Checking row %u for completeness: %u tiles\n", row, tower->max_row);

        if (row < GRID_HEIGHT && tower->max_row >= MAX_TILES_PER_ROW)
        {
            printf("Row %u is complete. Clearing row.\n", row);
            tower->max_row = 0;

            printf("Updating tower tiles starting from cleared row %u.\n", row);
            update_tiles(tower, row);

            tower->tile_count -= MAX_TILES_PER_ROW;
            printf("Tile count after clearing row %u: %u\n", row, tower->tile_count);
        }
        else
        {
            printf("Row %u is not complete. No clearing performed.\n", row);
        }

        if (row == 0)
        {
            break;
        }
    }
}

/*
----- FUNCTION: check_row -----
Purpose: checks the lowest row of the dropped active piece to see if all columns
            of that row has all tiles filled.

Parameters: Tower tower             tower address
            Tetromino active_piece  active_piece address

Return: TRUE       all columns are filled
        FALSE      at least one column is not filled

Limitations: - Model needs to be initialized with active_piece, pieces array, and playing_field properties.
*/
bool check_row(Tower *tower, Tetromino *active_piece)
{
    unsigned int row, lowest_row, rows_to_check;

    lowest_row = (active_piece->y + (active_piece->height - TILE_HEIGHT));
    rows_to_check = get_rows_to_check(active_piece);

    printf("Checking rows from lowest_row: %u\n", lowest_row);

    for (row = lowest_row; row > lowest_row - (rows_to_check * active_piece->velocity_y); row -= 15)
    {
        printf("Checking row: %u\n", row);

        if (check_tiles_in_row(tower, row))
        {
            printf("Row %u is filled!\n", row);
            return TRUE;
        }
    }

    printf("No filled row found.\n");
    return FALSE;
}

/*
----- FUNCTION: check_tiles_in_row -----
Purpose: checks to see if all tiles are filled and called by check_row

Parameters: Tower tower             tower address
            unsigned int row        y position of the row

Return:     TRUE  if all tiles_per_row is filled with a maximum of 10 tiles
            FALSE at least one tile is not filled
*/
bool check_tiles_in_row(Tower *tower, unsigned int row)
{
    unsigned int i, tile_x, tile_index;

    printf("Checking tiles in row: %u\n", row);

    for (tile_x = 225; tile_x <= 360; tile_x += 15)
    {
        printf("Checking tile index: %u\n", tile_index);

        tile_index = tower->tile_count;
        printf("Tile at index %u has coordinates (x: %d, y: %d)\n", tile_x, tower->tiles[tile_index].x, tower->tiles[tile_index].y);
        if ((tower->tiles[tile_index].y == row) && (tower->tiles[tile_index].x == tile_x))
        {
            printf("Tile found at row %u, column (x: %d, y: %d)\n", row, tower->tiles[tile_index].x, tower->tiles[tile_index].y);
            tower->max_row++;
        }
    }

    printf("Tiles found in row %u: %d\n", row, tower->max_row);
    if (tower->max_row == 10)
    {
        printf("Row %u is fully filled with 10 tiles.\n", row);
        return TRUE;
    }
    printf("Row %u is not fully filled (tiles found: %d).\n", row, tower->max_row);
    return FALSE;
}

/*
----- FUNCTION: get_rows_to_check -----
Purpose: decomposes the active_piece's height into its own rows

Parameters: Tetromino active_piece      active piece address

*/
unsigned int get_rows_to_check(Tetromino *active_piece)
{
    if (active_piece->curr_index == 1 || active_piece->curr_index == 2)
    {
        return 3;
    }
    else if (active_piece->curr_index >= 3 && active_piece->curr_index <= 6)
    {
        return 2;
    }
    return 4;
}
