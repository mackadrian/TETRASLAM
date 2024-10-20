/**
 * @file MODEL.C
 * @brief contains all of TETRASLAM's object behaviour functions.
 * @author Mack Bautista
 */

#include "model.h"
#include <stdlib.h>
#include <stdio.h> /*print collisions remove once done testing*/

/*NOTE: Remove print statements if the implementation is complete.*/

/*
----- FUNCTION: move_player_piece -----
Purpose: moves the player's active piece left, right;

Parameters: Tetromino active_piece       (active piece address)
            Field playing_field          (playing_field address)
            Direction direction          (LEFT or RIGHT directions)
            Tower tower                  (tower address)

Limitations: - Model needs to be initialized first otherwise this doesn't work.
*/
void move_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower, Direction direction)
{
    int premove_x;

    switch (direction)
    {
    case LEFT:
        if (active_piece->x > playing_field->x)
        {
            premove_x = active_piece->x - (TILE_WIDTH - 1);

            if (premove_x > playing_field->x)
            {
                active_piece->x = premove_x;
                if (check_tower_collision(active_piece, tower))
                {
                    active_piece->x += (TILE_WIDTH - 1);
                    printf("Tower collision detected on the left. Reverting to x: %d\n", active_piece->x);
                }
            }
            else
            {
                playing_field->collided = 1;
                printf("Left boundary collision detected for Tetromino at x: %d\n", active_piece->x);
            }
        }
        break;

    case RIGHT:
        if (active_piece->x + active_piece->width < playing_field->x + playing_field->width)
        {
            premove_x = active_piece->x + (TILE_WIDTH - 1);
            if (premove_x + active_piece->width < playing_field->x + playing_field->width)
            {
                active_piece->x = premove_x;
                if (check_tower_collision(active_piece, tower))
                {
                    active_piece->x -= (TILE_WIDTH - 1);
                    printf("Tower collision detected on the right. Reverting to x: %d\n", active_piece->x);
                }
            }
            else
            {
                playing_field->collided = 1;
                printf("Right boundary collision detected for Tetromino at x: %d\n", active_piece->x);
            }
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
        premove_y = active_piece->y + (TILE_HEIGHT - 1);
        if (active_piece->y + active_piece->height < (playing_field->y + playing_field->height - TILE_HEIGHT))
        {
            active_piece->y += (TILE_HEIGHT - 1);
            printf("Dropping piece to y: %d, x: %d\n", active_piece->y, active_piece->x);

            if (check_tower_collision(active_piece, tower))
            {
                active_piece->y -= (TILE_HEIGHT - 1);
                active_piece->merged = 1;
                tower->collided = 1;
                active_piece->dropped = 0;
                printf("Collision with tower detected, Tetromino merged at y: %d\n", active_piece->y);
                break;
            }
        }
        else
        {
            active_piece->y = (playing_field->y + playing_field->height - active_piece->height) - 1;
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

Parameters: Tetromino active_piece  (active_piece address)
            Tetromino pieces[]      (all of the 7 pieces address)
            Field playing_field     (playing_field address)
            Tower tower             (tower address)

Limitations: - Model needs to be initialized with active_piece, pieces array, and playing_field properties.
*/
void cycle_active_piece(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower)
{
    int next_index;
    unsigned int prev_x, prev_y, prev_width, prev_height;
    prev_x = active_piece->x;
    prev_y = active_piece->y;
    prev_width = active_piece->width;
    prev_height = active_piece->height;

    printf("Previous piece x: %u, y: %u\n", prev_x, prev_y);

    next_index = (active_piece->curr_index + 1) % 7;
    *active_piece = pieces[next_index];
    active_piece->curr_index = next_index;

    if (prev_x + active_piece->width > playing_field->x + playing_field->width - TILE_WIDTH)
    {
        printf("Cycled active piece is out of bounds at x:%u, y:%u\n",
               prev_x + active_piece->width, prev_y + active_piece->height);
        active_piece->x = (playing_field->x + playing_field->width - 1) - active_piece->width;
        printf("Adjust active piece at x:%u, y:%u, width: %u, height: %u,\n",
               active_piece->x, active_piece->y, active_piece->width, active_piece->height);
    }
    else
    {
        active_piece->x = prev_x;
        printf("No out of bounds occurred x:%u, y:%u, width: %u, height: %u,\n",
               active_piece->x, active_piece->y, active_piece->width, active_piece->height);
    }

    if (check_tower_collision(active_piece, tower))
    {
        printf("Collision detected with the tower after cycling at x:%u, y:%u\n", active_piece->x, active_piece->y);

        while (check_tower_collision(active_piece, tower) && active_piece->x + active_piece->width < playing_field->x + playing_field->width)
        {
            active_piece->x -= TILE_WIDTH - 1;
            printf("Adjusted active piece to avoid collision. New x: %u\n", active_piece->x);
        }
    }
}

/*
----- FUNCTION: reset_active_pos -----
Purpose: resets the player's position to the top centre of the playing field after merging
         with the tower.

Parameters: Tetromino player    (tetromino address)
            Tetromino pieces[]  (player_pieces address)
            Field playing_field (playing_field address)
            Tower tower         (tower address)

Limitations: - Resets the active piece to the original starting position.
*/
void reset_active_pos(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower)
{
    int shift_x = 0;
    int reload_index = active_piece->curr_index;
    merge_active_piece_to_tower(active_piece, tower);

    *active_piece = pieces[reload_index];
    active_piece->curr_index = reload_index;

    while (check_tower_collision(active_piece, tower))
    {
        active_piece->x += TILE_WIDTH - 1;
        shift_x++;

        if (active_piece->x + active_piece->width > playing_field->x + playing_field->width - TILE_WIDTH)
        {
            printf("No available space for the new active piece. Game over or handle this case.\n");
            return;
        }

        if (shift_x * (TILE_WIDTH - 1) >= playing_field->width)
        {
            printf("Unable to place the piece within the field. Game over or handle this case.\n");
            return;
        }
    }

    playing_field->collided = 0;
    tower->collided = 0;

    printf("Loaded next active piece. x: %d, y: %d, width: %d, height: %d\n",
           active_piece->x, active_piece->y, active_piece->width, active_piece->height);
}

/*
----- FUNCTION: merge_active_piece_to_tower -----
Purpose: upon colliding with the tower piece when dropped, the active piece becoems
         a part of the tower

Parameters: Tetromino active_piece  (active_piece address)
            Tower tower             (tower address)

Limitations: - Checks the collision between the active piece and the tower object.
             - Occurs when the player chooses to drop the piece as it checks for height.

*/
void merge_active_piece_to_tower(Tetromino *active_piece, Tower *tower)
{
    int i, new_tile_index;
    for (i = 0; i < active_piece->tile_count; i++)
    {
        new_tile_index = tower->tile_count;

        tower->tile[new_tile_index].x = active_piece->x;
        tower->tile[new_tile_index].y = active_piece->y + (i * (TILE_HEIGHT - 1));
        tower->tile[new_tile_index].width = TILE_WIDTH - 1;
        tower->tile[new_tile_index].height = TILE_HEIGHT - 1;

        tower->tile_count++;
    }

    printf("Merged active piece into tower. Tower now has %d tiles.\n", tower->tile_count);
}

/*
----- FUNCTION: clear_row -----
Purpose: playing field scans for complete columns and clears the column in that row

Parameters: Tetromino playing_field  (playing_field address)
            Tower tower              (tower address)

Limitations: - Checks the collision between the active piece and the tower object.
             - Occurs when the player chooses to drop the piece as it checks for height.

*/
void clear_row(Field *playing_field, Tower *tower)
{
    int i, row;
    for (row = playing_field->y + playing_field->height - TILE_HEIGHT; row >= playing_field->y; row -= TILE_HEIGHT)
    {
        if (check_row(row, playing_field, tower))
        {
            printf("Clearing row at y: %d\n", row);
            for (i = 0; i < tower->tile_count; i++)
            {
                Tile *tile = &tower->tile[i];
                if (tile->y == row)
                {

                    tile->y = -1;
                }
            }
            shift_rows(tower, playing_field);
        }
    }
}

/*
----- FUNCTION: shift_rows -----
Purpose: shifts the rows if there is a gap found in the tower
Parameters: Tower tower             (tower address)
            Field playing_field     (playing field address)

Limitations: - Checks the collision between the active piece and the tower object.
             - Occurs when the player chooses to drop the piece as it checks for height.

*/
void shift_rows(Tower *tower, Field *playing_field)
{
    int i, j, row, lowest_row, tile_falls, tile_below_found;
    for (row = playing_field->y + playing_field->height - TILE_HEIGHT; row >= playing_field->y; row -= TILE_HEIGHT)
    {
        tile_falls = 1;
        for (i = 0; i < tower->tile_count; i++)
        {
            Tile *tile = &tower->tile[i];

            if (tile->y == row)
            {
                tile_below_found = 0;

                for (j = 0; j < tower->tile_count; j++)
                {
                    if (tower->tile[j].x == tile->x && tower->tile[j].y == tile->y + TILE_HEIGHT)
                    {
                        tile_below_found = 1;
                        break;
                    }
                }
                if (tile_below_found)
                {
                    tile_falls = 0;
                    break;
                }
            }
        }

        if (tile_falls)
        {
            for (i = 0; i < tower->tile_count; i++)
            {
                Tile *tile = &tower->tile[i];
                if (tile->y == row)
                {
                    tile->y += TILE_HEIGHT;
                }
            }
        }
    }
}

/*
----- FUNCTION: check_row -----
Purpose: checks row for completed column

Parameters: Tetromino playing_field  (playing_field address)
            Tower tower              (tower address)

Return: int value                    (boolean int value)

Limitations: - Checks the collision between the active piece and the tower object.
             - Occurs when the player chooses to drop the piece as it checks for height.

*/
int check_row(int row, Field *playing_field, Tower *tower)
{
    int i, col, tiles_in_row, tile_found;
    tiles_in_row = 0;

    for (col = 0; col < 10; col++)
    {
        tile_found = 0;
        for (i = 0; i < tower->tile_count; i++)
        {
            Tile *tile = &tower->tile[i];
            if (tile->y == row && tile->x == playing_field->x + (col * TILE_WIDTH))
            {
                tile_found = 1;
                break;
            }
        }

        if (tile_found)
        {
            tiles_in_row++;
        }
    }

    return (tiles_in_row == 10) ? 1 : 0;
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
