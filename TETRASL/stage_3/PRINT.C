/**
 * @file PRINT.C
 * @brief contains all the function calls for printing
 * @author Mack Bautista
 */

#include "print.h"
#include "model.h"
#include <stdio.h>

/*
----- FUNCTION: print_model -----
Purpose: prints the model's properties to the screen.

Parameters: Model model     (pointer to the model address)

Limitations: - Model needs to be initialized first.
*/
void print_model(Model *model)
{
    int i;
    printf("Active Piece:\n");
    printf("    x=%u, y=%u, width=%u, height=%u, tile_count=%u, curr_index=%u, velocity_x=%d, velocity_y= %d, merged=%d, dropped=%d\n",
           model->active_piece.x,
           model->active_piece.y,
           model->active_piece.width,
           model->active_piece.height,
           model->active_piece.tile_count,
           model->active_piece.curr_index,
           model->active_piece.velocity_x,
           model->active_piece.velocity_y,
           model->active_piece.merged,
           model->active_piece.dropped);

    printf("Player Tetrominoes:\n");
    for (i = 0; i < 7; i++)
    {
        Tetromino *tetromino = &model->player_pieces[i];
        printf("  Tetromino %d: x=%u, y=%u, width=%u, height=%u, tile_count=%u, curr_index=%u, velocity_x=%d, velocity_y= %d, merged=%d, dropped=%d\n",
               i,
               tetromino->x,
               tetromino->y,
               tetromino->width,
               tetromino->height,
               tetromino->tile_count,
               tetromino->curr_index,
               tetromino->velocity_x,
               tetromino->velocity_y,
               tetromino->merged,
               tetromino->dropped);
    }

    printf("Playing Field:\n");
    printf("  x=%u, y=%u, width=%u, height=%u\n",
           model->playing_field.x,
           model->playing_field.y,
           model->playing_field.width,
           model->playing_field.height);

    printf("Tower:\n");
    printf(" tile_count=%d\n",
           model->tower.tile_count);

    printf("Tiles in Tower:\n");
    for (i = 0; i < model->tower.tile_count; i++)
    {
        Tile *tile = &model->tower.tiles[i];
        if (tile->x != 0 || tile->y != 0)
        {
            printf("  Tiles %d: x=%u, y=%u, width=%u, height=%u\n",
                   i,
                   tile->x,
                   tile->y,
                   tile->width,
                   tile->height);
        }
    }

    printf("Tile Counter:\n");
    printf("  x=%u, y=%u, tile_count=%u\n",
           model->counter.x,
           model->counter.y,
           model->counter.tile_count);
}

/*
----- FUNCTION: print_tetrominoes -----
Purpose: prints all the player_piece's properties to the screen.

Parameters: Tetromino player_pieces     (player_pieces address)

Limitations: - Player pieces needs to be initialized first.
*/
void print_tetrominoes(Tetromino player_pieces[7])
{
    int i;
    printf("Player Tetrominoes:\n");
    for (i = 0; i < 7; i++)
    {
        Tetromino *tetromino = &player_pieces[i];
        printf("  Tetromino %d: x=%u, y=%u, width=%u, height=%u, tile_count=%u, velocity_x=%d, velocity_y=%d, merged=%d, dropped=%d\n",
               i,
               tetromino->x,
               tetromino->y,
               tetromino->width,
               tetromino->height,
               tetromino->tile_count,
               tetromino->velocity_x,
               tetromino->velocity_y,
               tetromino->merged,
               tetromino->dropped);
    }
}

/*
----- FUNCTION: print_playing_field -----
Purpose: prints the playing field properties to the screen.

Parameters: Field playing_field    (playing_field address)

Limitations: - Playing field needs to be initialized first.
*/
void print_playing_field(Field *playing_field)
{
    printf("Playing Field:\n");
    printf("  x=%u, y=%u, width=%u, height=%u\n",
           playing_field->x,
           playing_field->y,
           playing_field->width,
           playing_field->height);
}

/*
----- FUNCTION: print_tower -----
Purpose: prints the tower properties and tile positions to the screen.

Parameters: Tower tower    (tower address)

Limitations: - Tower needs to be initialized first.
             - Tiles has to be randomized and initialized first.
*/
void print_tower(Tower *tower)
{
    int i;
    printf("Tower:\n");
    printf("  tile_count=%d\n",
           tower->tile_count);

    printf("Tiles in Tower:\n");
    for (i = 0; i < tower->tile_count; i++)
    {
        Tile *tile = &tower->tiles[i];
        if (tile->x != 0 || tile->y != 0)
        {
            printf("  Tile %d: x=%u, y=%u, width=%u, height=%u\n",
                   i,
                   tile->x,
                   tile->y,
                   tile->height,
                   tile->width);
        }
    }
}

/*
----- FUNCTION: print_counter -----
Purpose: prints the counter properties to the screen.

Parameters: Counter counter    (counter address)

Limitations: - Counter needs to be initialized first.
*/
void print_counter(Counter *counter)
{
    printf("Tile Counter:\n");
    printf("  x=%u, y=%u, tile_count=%u\n",
           counter->x,
           counter->y,
           counter->tile_count);
}

/*
----- FUNCTION: print_active_piece -----
Purpose: prints the active piece's properties to the screen

Parameters: Tetromino active_piece      (active_piece address)

Limitations: - Active piece has to be initialized first
*/
void print_active_piece(Tetromino *player_piece)
{
    printf("Active Piece:\n");
    printf("    x=%u, y=%u, width=%u, height=%u, tile_count=%u, curr_index=%u, merged=%d, dropped=%d\n",
           player_piece->x,
           player_piece->y,
           player_piece->width,
           player_piece->height,
           player_piece->tile_count,
           player_piece->curr_index,
           player_piece->merged,
           player_piece->dropped);
}