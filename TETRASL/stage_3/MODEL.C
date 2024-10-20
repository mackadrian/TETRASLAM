/**
 * @file MODEL.C
 * @brief contains all of TETRASLAM's object behaviour functions.
 * @author Mack Bautista
 */

#include "model.h"
#include <stdlib.h>
#include <stdio.h> /*print collisions remove once done testing*/

#define MAX_COLUMNS 10
#define OFFSET 1
/*NOTE: Remove print statements if the implementation is complete.*/

/*
----- FUNCTION: move_player_piece -----
Purpose: moves the player's active piece left, right;

Parameters: Tetromino active_piece       (active piece address)
            Field playing_field          (playing_field address)
            Direction direction          (LEFT or RIGHT directions)

Limitations: - Model needs to be initialized first otherwise this doesn't work.
             - The active player piece in the playing field is the only one that moves.
*/
void move_active_piece(Tetromino *active_piece, Field *playing_field, Direction direction)
{
    int premove_x;

    switch (direction)
    {
    case LEFT:
        if (active_piece->x > playing_field->x)
        {
            premove_x = active_piece->x - (TILE_WIDTH - 1);

            if (premove_x >= playing_field->x)
            {

                active_piece->x = premove_x;
            }
            else
            {

                playing_field->collided = 1;
                printf("Left boundary collision detected for Tetromino at x: %d\n", active_piece->x);
            }
        }
        break;

    case RIGHT:
        if (active_piece->x + TILE_WIDTH - 1 < (playing_field->x + playing_field->width) - TILE_WIDTH)
        {
            active_piece->x += TILE_WIDTH - 1;
        }
        else
        {
            playing_field->collided = 1;
            printf("Right boundary collision detected for Tetromino at x: %d\n", active_piece->x);
        }
        break;
    }
}

/*
----- FUNCTION: drop_active_piece -----
Purpose: drops the active piece in the playing field

Parameters: Tetromino active_piece      (active_piece address)
            Tetromino playing_field     (playing_field address)
            Tower tower                 (tower address)

Limitations: - Model needs to be initialized with the proper active_piece, playing_field, and tower properties.
*/
void drop_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower)
{
    int premove_y;
    active_piece->dropped = 1;

    while (active_piece->dropped)
    {
        premove_y = active_piece->y - (TILE_HEIGHT - 1);
        if (active_piece->y + TILE_HEIGHT < playing_field->y + playing_field->height)
        {
            active_piece->y += TILE_HEIGHT - 1;

            /* Debugging output */
            printf("Dropping piece to y: %d, x: %d\n", active_piece->y, active_piece->x);

            if (check_tower_collision(active_piece, tower))
            {
                active_piece->merged = 1;
                tower->collided = 1;
                active_piece->dropped = 0;
                printf("Collision with tower detected, Tetromino merged at y: %d\n", active_piece->y);
                break;
            }
        }
        else
        {
            active_piece->y = playing_field->y + playing_field->height - active_piece->height;
            active_piece->merged = 1;
            playing_field->collided = 1;
            active_piece->dropped = 0;
            printf("Collision with playing field bottom border detected at y: %d\n", active_piece->y);
            break;
        }
    }
}

/*
----- FUNCTION: cycle_active_piece -----
Purpose: cycles the active piece to the next piece.

Parameters: Tetromino active_piece      (active_piece address)
            Tetromino pieces            (all of the 7 pieces address)

Limitations: - Model needs to be initialized with active_piece, pieces array, and playing_field properties.
*/

/*TODO work on dimension and boundaries for different pieces*/
void cycle_active_piece(Tetromino *active_piece, Tetromino pieces[], Field *playing_field)
{
    int new_index;
    Tetromino *curr_piece = active_piece;

    printf("Current piece: x: %d, y: %d\n", curr_piece->x, curr_piece->y);

    /* Get the new piece index */
    new_index = (active_piece->curr_index + 1) % 7;

    /* Temporarily store the new piece */
    Tetromino new_piece = pieces[new_index];
    new_piece.curr_index = new_index;

    /* Ensure the new piece will fit within the playing field */
    if (curr_piece->x + new_piece.width > playing_field->x + playing_field->width)
    {
        /* Adjust x position if it goes out of bounds */
        new_piece.x = (playing_field->x + playing_field->width) - new_piece.width;
    }
    else
    {
        /* Assign the current piece's x position to the new piece */
        new_piece.x = curr_piece->x;
    }

    /* Ensure the new piece's height also fits within the playing field */
    if (curr_piece->y + new_piece.height > playing_field->y + playing_field->height)
    {
        /* Adjust y position if it goes out of bounds */
        new_piece.y = (playing_field->y + playing_field->height) - new_piece.height;
    }
    else
    {
        /* Assign the current piece's y position to the new piece */
        new_piece.y = curr_piece->y;
    }

    /* Now set the active piece to the new piece */
    *active_piece = new_piece;

    printf("Cycled to tetromino (index: %d) at x: %d, y: %d\n", new_index, active_piece->x, active_piece->y);
}

/*
----- FUNCTION: reset_active_pos -----
Purpose: resets the player's position to the top centre of the playing field after merging
         with the tower.

Parameters: Tetromino player    (tetromino address)

Limitations: - Resets the active piece to the original starting position.
*/
void reset_active_pos(Tetromino *active_piece, Field *playing_field, Tower *tower)
{
    active_piece->x = playing_field->x + (15 * 4) + 1;
    active_piece->y = playing_field->y + 1;
    active_piece->merged = 0;
    active_piece->dropped = 0;
    playing_field->collided = 0;
    tower->collided = 0;
}

/*
----- FUNCTION: check_tower_collision -----
Purpose: checks the tower collision between the player and the tower

Parameters: Tetromino player    (pointer to player's tetromino)
            Tower tower         (pointer to tower address)

Return:     int value           (boolean value)

Limitations: - Checks the collision between the active piece and the tower object.
             - Occurs when the player chooses to drop the piece as it checks for height.

*/
int check_tower_collision(Tetromino *active_piece, Tower *tower)
{
    int i, has_collided;
    has_collided = 0;

    for (i = 0; i < tower->tile_count; i++)
    {
        Tile *tile = &tower->tile[i];

        if (active_piece->x + 1 < tile->x + tile->width &&
            active_piece->x + active_piece->width - 1 > tile->x &&
            active_piece->y + 1 < tile->y + tile->height &&
            active_piece->y + active_piece->height - 1 > tile->y)
        {
            has_collided = 1;
            tower->collided = has_collided;
            printf("Collision detected with tile at x: %u, y: %u\n", tile->x, tile->y);
        }
    }

    return has_collided;
}
