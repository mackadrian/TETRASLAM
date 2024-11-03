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
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define CONST_VELOCITY 15

/*
----- FUNCTION: initialize_tile -----
Purpose: initializes a tile
Limitations: - Assumes that every tile is 16x16 size.
*/
void initialize_tile(Tile *new_tile, unsigned int x, unsigned int y)
{
    new_tile->x = x;
    new_tile->y = y;
    new_tile->width = TILE_WIDTH;
    new_tile->height = TILE_HEIGHT;
}

/*
----- FUNCTION: initialize_tetromino -----
Purpose: initializes a tetromino
Limitations: - Fixed x-velocity and y-velocity at 15.
*/
void initialize_tetromino(Tetromino *new_tetromino, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
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
    unsigned int i = 0;

    new_tower->tile_count = tile_count;

    while (i < tile_count)
    {
        initialize_tile(&new_tower->tiles[0], 0, 0);
        i++;
    }

    for (i = 0; i < MAX_TILES_PER_ROW; i++)
    {
        new_tower->tiles_per_row[i] = 0;
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
----- FUNCTION: update_tower -----
Purpose: Updates the tower by merging the active piece into the tower and updating the tower's state.
*/
void update_tower(Tetromino *active_piece, Tower *tower)
{
    switch (active_piece->curr_index)
    {
    case 0:
        update_IJL_piece(active_piece, tower, I_PIECE_LAYOUT, 4);
        break;
    case 1:
        update_IJL_piece(active_piece, tower, J_PIECE_LAYOUT, 3);
        break;
    case 2:
        update_IJL_piece(active_piece, tower, L_PIECE_LAYOUT, 3);
        break;
    case 3:
        update_O_piece(active_piece, tower);
        break;
    case 4:
        update_STZ_piece(active_piece, tower, S_PIECE_LAYOUT);
        break;
    case 5:
        update_STZ_piece(active_piece, tower, T_PIECE_LAYOUT);
        break;
    case 6:
        update_STZ_piece(active_piece, tower, Z_PIECE_LAYOUT);
        break;
    default:
        break;
    }

    active_piece->merged = TRUE;
}

/*
----- FUNCTION: update_IJL_pieces -----
Purpose: updates the IJL pieces, called by the update_tower.
*/
void update_IJL_piece(Tetromino *active_piece, Tower *tower, const int layout[4][2], int height)
{
    unsigned int i, j, tile_index;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if (layout[i][j] == 1)
            {
                tile_index = tower->tile_count;
                tower->tiles[tile_index].x = active_piece->x + (j * active_piece->velocity_x);
                tower->tiles[tile_index].y = active_piece->y + (i * active_piece->velocity_y);

                tower->tiles[tile_index].width = TILE_WIDTH;
                tower->tiles[tile_index].height = TILE_HEIGHT;

                tower->tile_count++;
            }
        }
    }
}

/*
----- FUNCTION: update_O_piece -----
Purpose: updates the O piece, called by the update_tower.
*/
void update_O_piece(Tetromino *active_piece, Tower *tower)
{
    unsigned int i, j, tile_index;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if (O_PIECE_LAYOUT[i][j] == 1)
            {
                tile_index = tower->tile_count;
                tower->tiles[tile_index].x = active_piece->x + (j * TILE_WIDTH);
                tower->tiles[tile_index].y = active_piece->y + (i * TILE_HEIGHT);

                tower->tiles[tile_index].width = active_piece->velocity_x;
                tower->tiles[tile_index].height = active_piece->velocity_y;

                tower->tile_count++;
            }
        }
    }
}

/*
----- FUNCTION: update_STZ_pieces -----
Purpose: updates the STZ pieces, called by the update_tower.
*/
void update_STZ_piece(Tetromino *active_piece, Tower *tower, const int layout[2][3])
{
    unsigned int i, j, tile_index;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (layout[i][j] == 1)
            {
                tile_index = tower->tile_count;
                tower->tiles[tile_index].x = active_piece->x + (j * active_piece->velocity_x);
                tower->tiles[tile_index].y = active_piece->y + (i * active_piece->velocity_y);

                tower->tiles[tile_index].width = TILE_WIDTH;
                tower->tiles[tile_index].height = TILE_HEIGHT;

                tower->tile_count++;
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
