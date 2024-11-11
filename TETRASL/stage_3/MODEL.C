/**
 * @file MODEL.C
 * @brief contains all of TETRASLAM's object behaviour functions.
 * @author Mack Bautista
 */

#include "model.h"
#include "layout.h"
#include <stdlib.h>
#include <stdio.h>

#define OFFSET 1
#define FIELD_X_OFFSET 225
#define FIELD_Y_OFFSET 41
#define CONST_VELOCITY 15

/*
----- FUNCTION: cycle_piece_layout -----
Purpose: returns the layout corresponding to the current piece's index.
*/
const int (*cycle_piece_layout(int curr_index))[PIECE_SIZE]
{
    switch (curr_index)
    {
    case 0:
        return I_PIECE_LAYOUT;
    case 1:
        return J_PIECE_LAYOUT;
    case 2:
        return L_PIECE_LAYOUT;
    case 3:
        return O_PIECE_LAYOUT;
    case 4:
        return S_PIECE_LAYOUT;
    case 5:
        return T_PIECE_LAYOUT;
    case 6:
        return Z_PIECE_LAYOUT;
    default:
        return NULL;
    }
}

/*
----- FUNCTION: get_grid_coordinates -----
Purpose: converts the (x,y) pixel coordinates into grid coordinates to be used
            within the grid layout
Formula: grid position = (x - 225) / 15

Limitations:
*/
void get_grid_coordinates(unsigned int x, unsigned int y,
                          unsigned int *grid_x, unsigned int *grid_y)
{
    *grid_x = (x - FIELD_X_OFFSET) / CONST_VELOCITY;
    *grid_y = (y - FIELD_Y_OFFSET) / CONST_VELOCITY;
}

/*
----- FUNCTION: initialize_tile -----
Purpose: initializes a tile
Limitations: - Assumes that every tile is 16x16 size.
*/
void initialize_tile(Tower *tower, Tile *new_tile, unsigned int x, unsigned int y)
{
    unsigned int grid_x, grid_y;

    new_tile->x = x;
    new_tile->y = y;
    new_tile->width = TILE_WIDTH;
    new_tile->height = TILE_HEIGHT;

    get_grid_coordinates(x, y, &grid_x, &grid_y);
    if (grid_x >= 0 && grid_x < GRID_WIDTH && grid_y >= 0 && grid_y < GRID_HEIGHT)
    {
        tower->grid[grid_y][grid_x] = 1;
    }
}

/*
----- FUNCTION: initialize_layout -----
Purpose: initializes the tetromino layout with its own type
Limitations: -
*/
void initialize_layout(Tetromino *new_tetromino, TetrominoType type)
{
    unsigned int i, j;
    const int(*layout)[PIECE_SIZE] = NULL;

    switch (type)
    {
    case I_PIECE:
        layout = I_PIECE_LAYOUT;
        break;
    case J_PIECE:
        layout = J_PIECE_LAYOUT;
        break;
    case L_PIECE:
        layout = L_PIECE_LAYOUT;
        break;
    case O_PIECE:
        layout = O_PIECE_LAYOUT;
        break;
    case S_PIECE:
        layout = S_PIECE_LAYOUT;
        break;
    case T_PIECE:
        layout = T_PIECE_LAYOUT;
        break;
    case Z_PIECE:
        layout = Z_PIECE_LAYOUT;
        break;
    default:
        return;
    }

    for (i = 0; i < PIECE_SIZE; i++)
    {
        for (j = 0; j < PIECE_SIZE; j++)
        {
            new_tetromino->layout[i][j] = layout[i][j];
        }
    }
}

/*
----- FUNCTION: initialize_tetromino -----
Purpose: initializes a tetromino
Limitations: - Fixed x-velocity and y-velocity at 15.
*/
void initialize_tetromino(Tetromino *new_tetromino, unsigned int x, unsigned int y, unsigned int width, unsigned int height, TetrominoType type)
{
    new_tetromino->x = x;
    new_tetromino->y = y;
    new_tetromino->width = width;
    new_tetromino->height = height;
    new_tetromino->tile_count = MAX_TILES_PER_TETROMINO;
    new_tetromino->curr_index = 0;
    new_tetromino->velocity_x = CONST_VELOCITY;
    new_tetromino->velocity_y = CONST_VELOCITY;
    new_tetromino->merged = FALSE;
    new_tetromino->dropped = FALSE;

    initialize_layout(new_tetromino, type);
}

/*
----- FUNCTION: initialize_field -----
Purpose: initializes the playing field
Limitations: - Must know the size of playing field and game occurs within that boundary.
*/
void initialize_field(Field *new_field, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    new_field->x = x;
    new_field->y = y;
    new_field->width = width;
    new_field->height = height;
}

/*
----- FUNCTION: initialize_tower -----
Purpose: initializes the tower
Limitations: - Tower is initialized but not the positions of the tiles.
*/
void initialize_tower(Tower *new_tower, unsigned int tile_count)
{
    unsigned int i, row, col;
    new_tower->max_row = 0;
    new_tower->tile_count = tile_count;

    while (i < tile_count)
    {
        initialize_tile(new_tower, &new_tower->tiles[i], 0, 0);
        i++;
    }

    for (row = 0; row < GRID_HEIGHT; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            new_tower->grid[row][col] = GRID_LAYOUT[row][col];
        }
    }
}

/*
----- FUNCTION: initialize_counter -----
Purpose: initializes the counter
*/
void initialize_counter(Counter *new_counter, unsigned int x, unsigned int y, int tile_count)
{
    new_counter->x = x;
    new_counter->y = y;
    new_counter->tile_count = tile_count;
}

/*
----- FUNCTION: update_counter -----
Purpose: updates the tile counter based on the tower tile counts
*/
void update_counter(Counter *counter, Tower *tower)
{
    counter->tile_count = tower->tile_count;
}

/*
----- FUNCTION: update_active_piece -----
Purpose: updates the player controlled active piece
*/
void update_active_piece(Tetromino *active_piece, Direction direction)
{
    switch (direction)
    {
    case LEFT:
        active_piece->x -= active_piece->velocity_x;
        break;
    case RIGHT:
        active_piece->x += active_piece->velocity_x;
        break;
    case DROP:
        active_piece->y += active_piece->velocity_y;
        break;
    }
}

/*
----- FUNCTION: update_tiles -----
Purpose: updates the tiles in tower shifting the y-position downwards.
*/
void update_tiles(Tower *tower, unsigned int row)
{
}

/*
----- FUNCTION: update_tower -----
Purpose: Updates the tower by merging the active piece into the tower and updating the tower's state.
*/
void update_tower(Tetromino *active_piece, Tower *tower)
{
    unsigned int rows, cols;
    const int(*layout)[PIECE_SIZE] = NULL;
    rows = 0;
    cols = 0;

    layout = cycle_piece_layout(active_piece->curr_index);
    update_piece_layout(active_piece, tower, layout);
    active_piece->merged = TRUE;
}

/*
----- FUNCTION: update_piece_layout -----
Purpose: Updates the tower by merging the active piece into the tower and updating the tower's state.
*/
void update_piece_layout(Tetromino *active_piece, Tower *tower, const int layout[PIECE_SIZE][PIECE_SIZE])
{
    unsigned int i, j, tile_index;
    unsigned int grid_x, grid_y;

    for (i = 0; i < PIECE_SIZE; i++)
    {
        for (j = 0; j < PIECE_SIZE; j++)
        {
            if (layout[i][j] == 1)
            {
                tile_index = tower->tile_count;
                tower->tiles[tile_index].x = active_piece->x + (j * active_piece->velocity_x);
                tower->tiles[tile_index].y = active_piece->y + (i * active_piece->velocity_y);
                tower->tiles[tile_index].width = TILE_WIDTH;
                tower->tiles[tile_index].height = TILE_HEIGHT;
                tower->tile_count++;

                get_grid_coordinates(active_piece->x + j * active_piece->velocity_x,
                                     active_piece->y + i * active_piece->velocity_y,
                                     &grid_x, &grid_y);
                if (grid_x < GRID_WIDTH && grid_y < GRID_HEIGHT)
                {
                    tower->grid[grid_y][grid_x] = 1;
                }
            }
        }
    }
}

/*
----- FUNCTION: clear_row -----
Purpose: clears the row of the lowest tile position of an active piece.
*/

/*
----- FUNCTION: out_of_bounds_collision -----
Purpose: checks to see if player is out of bounds of the playing area
*/
bool player_bounds_collision(Tetromino *active_piece, Field *playing_field)
{
    if (active_piece->x < playing_field->x ||
        active_piece->x + active_piece->width > playing_field->x + playing_field->width)
    {
        return TRUE;
    }

    if (active_piece->y < playing_field->y ||
        active_piece->y + active_piece->height > playing_field->y + playing_field->height)
    {
        return TRUE;
    }

    return FALSE;
}

/*
----- FUNCTION: tile_collision -----
Purpose: checks to see if player has collided with any tiles
Assumptions: collision hit size is 15x15 instead of 16x16 due to overlapping edges
*/
bool tile_collision(Tetromino *active_piece, Tile *tile)
{
    if (active_piece->x + OFFSET < tile->x + tile->width &&
        active_piece->x + active_piece->width - OFFSET > tile->x &&
        active_piece->y + OFFSET < tile->y + tile->height &&
        active_piece->y + active_piece->height - OFFSET > tile->y)
    {
        return TRUE;
    }

    return FALSE;
}

/*
----- FUNCTION: tower_collision -----
Purpose: checks to see if player has collided with any of tower's tiles
*/
bool tower_collision(Tetromino *active_piece, Tower *tower)
{
    unsigned int i;
    for (i = 0; i < tower->tile_count; i++)
    {
        Tile *current_tile = &tower->tiles[i];
        if (tile_collision(active_piece, current_tile))
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*
----- FUNCTION: fatal_tower_collision -----
Purpose: checks to see if tower collides with the playing field's top
*/
bool fatal_tower_collision(Tower *tower, Field *playing_field)
{
    unsigned int i;
    for (i = 0; i < tower->tile_count; i++)
    {
        Tile *current_tile = &tower->tiles[i];
        if (current_tile->y <= playing_field->y + OFFSET)
        {
            return TRUE;
        }
    }

    return FALSE;
}
