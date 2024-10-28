/**
 * @file T_RENDER.C
 * @brief tests how each model and bitmaps is rendered to the screen.
 * @author Mack Bautista
 */

#include "events.h"
#include "render.h"
#include <osbind.h>
#include <stdio.h>

int main()
{
    Model create_model;
    Model *model = &create_model;
    UINT32 *base_32 = (UINT32 *)Physbase();
    UINT16 *base_16 = (UINT16 *)Physbase();
    UINT8 *base_8 = (UINT8 *)Physbase();
    printf("\033E\033f\n");

    initialize_tetromino(&model->active_piece, 285, 41, 16, 61);
    initialize_field(&model->playing_field, 224, 40, 153, 303);
    initialize_counter(&model->counter, 224 + 153 + 32, 40, 5);

    initialize_tetromino(&model->player_pieces[0], 285, 41, 16, 61);
    initialize_tetromino(&model->player_pieces[1], 285, 41, 31, 46);
    initialize_tetromino(&model->player_pieces[2], 285, 41, 31, 46);
    initialize_tetromino(&model->player_pieces[3], 285, 41, 31, 31);
    initialize_tetromino(&model->player_pieces[4], 285, 41, 46, 31);
    initialize_tetromino(&model->player_pieces[5], 285, 41, 46, 31);
    initialize_tetromino(&model->player_pieces[6], 285, 41, 46, 31);

    initialize_tower(&model->tower, 5);
    initialize_tile(&model->tower.tiles[0], 255, 41 + (15 * 4));
    initialize_tile(&model->tower.tiles[1], 255 + (15 * 2), 41 + (15 * 4));
    initialize_tile(&model->tower.tiles[2], 255 + (15 * 3), 41 + (15 * 4));
    initialize_tile(&model->tower.tiles[3], 255 + (15 * 6), 41 + (15 * 4));
    initialize_tile(&model->tower.tiles[4], 255 + (15 * 7), 41 + (15 * 4));

    render(model, base_32, base_16, base_8);

    return 0;
}
