/**
 * @file EVENTS.C
 * @brief contains all of TETRASLAM's event functions.
 * @author Mack Bautista
 */

#include "EVENTS.H"
#include <stdio.h>
/*
----- FUNCTION: move_player_piece -----
Purpose: moves the player's active piece left, right;

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

    if (out_of_bounds_collision(active_piece, playing_field))
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

        if (out_of_bounds_collision(active_piece, playing_field))
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
----- FUNCTION: reset_active_pos -----
Purpose: resets the player's position to the top centre of the playing field after merging
         with the tower.

Parameters: Tetromino player    (tetromino address)
            Tetromino pieces[]  (player_pieces address)
            Field playing_field (playing_field address)
            Tower tower         (tower address)

Limitations: - Resets the active piece to the original starting position.
*/
void reset_active_piece(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower)
{
    int reload_index = active_piece->curr_index;
    update_tower(active_piece, tower);

    *active_piece = pieces[reload_index];
    active_piece->curr_index = reload_index;

    printf("Loaded next active piece at x: %d, y: %d, width: %d, height: %d\n",
           active_piece->x, active_piece->y, active_piece->width, active_piece->height);
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
    int next_index = (active_piece->curr_index + 1) % 7;

    unsigned int prev_x = active_piece->x;
    unsigned int prev_y = active_piece->y;

    *active_piece = pieces[next_index];
    active_piece->curr_index = next_index;

    printf("Cycling active piece. Previous piece x: %u, y: %u\n", prev_x, prev_y);

    if (out_of_bounds_collision(active_piece, playing_field))
    {
        printf("Cycled active piece is out of bounds at x:%u, y:%u\n", active_piece->x, active_piece->y);
        active_piece->x = prev_x;
    }
    else
    {
        printf("No out of bounds occurred x:%u, y:%u\n", active_piece->x, active_piece->y);
    }

    if (tower_collision(active_piece, tower))
    {
        printf("Collision detected with the tower after cycling at x:%u, y:%u\n", active_piece->x, active_piece->y);
        while (tower_collision(active_piece, tower) && active_piece->x + active_piece->width < playing_field->x + playing_field->width)
        {
            active_piece->x -= active_piece->velocity_x;
            printf("Adjusted active piece to avoid collision. New x: %u\n", active_piece->x);
        }
    }
}