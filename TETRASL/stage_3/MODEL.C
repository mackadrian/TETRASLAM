/**
 * @file MODEL.C
 * @brief contains all of TETRASLAM's object behaviour functions.
 * @author Mack Bautista
 */

#include "model.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

/*
----- FUNCTION: initialize_tile -----
Purpose: initializes a tile

Limitations: - Assumes that every tile is 16x16 size.
*/
void initialize_tile(Tile *new_tile, unsigned int x, unsigned int y)
{
    new_tile->x = x;
    new_tile->y = y;
    new_tile->width = 16;
    new_tile->height = 16;
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
    new_tetromino->tile_count = 4;
    new_tetromino->curr_index = 0;
    new_tetromino->velocity_x = 15;
    new_tetromino->velocity_y = 15;
    new_tetromino->merged = FALSE;
    new_tetromino->dropped = FALSE;
}

/*
----- FUNCTION: initialize_field -----
Purpose: initializes the playing field

Limitations: - Must know the size of playing field and understand game occurs within that boundary.
*/
void initialize_field(Field *new_field, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    new_field->x = x;
    new_field->y = y;
    new_field->width = width;
    new_field->height = height;
    new_field->collision = FALSE;
}

/*
----- FUNCTION: initialize_tower -----
Purpose: initializes the tower

Limitations: - Tower is initialized but not the positions of the tiles.
*/
void initialize_tower(Tower *new_tower, unsigned int x, unsigned int y,
                      unsigned int width, unsigned int height, unsigned int tile_count)
{
    unsigned int i = 0;

    new_tower->x = x;
    new_tower->y = y;
    new_tower->width = width;
    new_tower->height = height;
    new_tower->tile_count = tile_count;
    new_tower->collision = FALSE;

    while (i < tile_count)
    {
        initialize_tile(&new_tower->tiles[0], 0, 0);
        i++;
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
Purpose: updates the tile counter
*/
void update_counter(Counter *counter)
{
    (counter->tile_count)++;
}
