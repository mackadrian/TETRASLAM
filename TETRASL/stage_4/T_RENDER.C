/**
 * @file T_RENDER.C
 * @brief tests how each model and bitmaps are rendered to the screen.
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

    initialize_tetromino(&model->active_piece, 285, 41, 16, 61, I_PIECE);
    initialize_field(&model->playing_field, 224, 40, 153, 303);
    initialize_counter(&model->counter, 224 + 153 + 32, 40, 78);

    initialize_tetromino(&model->player_pieces[0], 285, 41, 16, 61, I_PIECE);
    initialize_tetromino(&model->player_pieces[1], 285, 41, 31, 46, J_PIECE);
    initialize_tetromino(&model->player_pieces[2], 285, 41, 31, 46, L_PIECE);
    initialize_tetromino(&model->player_pieces[3], 285, 41, 31, 31, O_PIECE);
    initialize_tetromino(&model->player_pieces[4], 285, 41, 46, 31, S_PIECE);
    initialize_tetromino(&model->player_pieces[5], 285, 41, 46, 31, T_PIECE);
    initialize_tetromino(&model->player_pieces[6], 285, 41, 46, 31, Z_PIECE);

    /*Plotting tiles */
    initialize_tower(&model->tower, 78);
    /*Row 4*/
    initialize_tile(&model->tower, &model->tower.tiles[0], 225, 41 + (15 * 3));
    initialize_tile(&model->tower, &model->tower.tiles[1], 225 + (15 * 9), 41 + (15 * 3));
    /*Row 5*/
    initialize_tile(&model->tower, &model->tower.tiles[2], 225, 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[3], 225 + (15 * 2), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[4], 225 + (15 * 3), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[5], 225 + (15 * 6), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[6], 225 + (15 * 7), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[7], 225 + (15 * 9), 41 + (15 * 4));
    /*Row 6*/
    initialize_tile(&model->tower, &model->tower.tiles[8], 225 + (15 * 3), 41 + (15 * 5));
    initialize_tile(&model->tower, &model->tower.tiles[9], 225 + (15 * 4), 41 + (15 * 5));
    initialize_tile(&model->tower, &model->tower.tiles[10], 225 + (15 * 5), 41 + (15 * 5));
    initialize_tile(&model->tower, &model->tower.tiles[11], 225 + (15 * 6), 41 + (15 * 5));
    /*Row 7*/
    initialize_tile(&model->tower, &model->tower.tiles[12], 225 + 15, 41 + (15 * 6));
    initialize_tile(&model->tower, &model->tower.tiles[13], 225 + (15 * 8), 41 + (15 * 6));
    /*Row 8*/
    initialize_tile(&model->tower, &model->tower.tiles[14], 225, 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[15], 225 + (15 * 2), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[16], 225 + (15 * 3), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[17], 225 + (15 * 4), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[18], 225 + (15 * 5), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[19], 225 + (15 * 6), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[20], 225 + (15 * 7), 41 + (15 * 7));
    initialize_tile(&model->tower, &model->tower.tiles[21], 225 + (15 * 9), 41 + (15 * 7));
    /*Row 9*/
    initialize_tile(&model->tower, &model->tower.tiles[22], 225, 41 + (15 * 8));
    initialize_tile(&model->tower, &model->tower.tiles[23], 225 + (15 * 2), 41 + (15 * 8));
    initialize_tile(&model->tower, &model->tower.tiles[24], 225 + (15 * 3), 41 + (15 * 8));
    initialize_tile(&model->tower, &model->tower.tiles[25], 225 + (15 * 6), 41 + (15 * 8));
    initialize_tile(&model->tower, &model->tower.tiles[26], 225 + (15 * 7), 41 + (15 * 8));
    initialize_tile(&model->tower, &model->tower.tiles[27], 225 + (15 * 9), 41 + (15 * 8));
    /*Row 10*/
    initialize_tile(&model->tower, &model->tower.tiles[28], 225, 41 + (15 * 9));
    initialize_tile(&model->tower, &model->tower.tiles[29], 225 + (15 * 4), 41 + (15 * 9));
    initialize_tile(&model->tower, &model->tower.tiles[30], 225 + (15 * 5), 41 + (15 * 9));
    initialize_tile(&model->tower, &model->tower.tiles[31], 225 + (15 * 9), 41 + (15 * 9));
    /*Row 11*/
    initialize_tile(&model->tower, &model->tower.tiles[32], 225 + 15, 41 + (15 * 10));
    initialize_tile(&model->tower, &model->tower.tiles[33], 225 + (15 * 4), 41 + (15 * 10));
    initialize_tile(&model->tower, &model->tower.tiles[34], 225 + (15 * 5), 41 + (15 * 10));
    initialize_tile(&model->tower, &model->tower.tiles[35], 225 + (15 * 8), 41 + (15 * 10));
    /*Row 12*/
    initialize_tile(&model->tower, &model->tower.tiles[36], 225 + (15 * 2), 41 + (15 * 11));
    initialize_tile(&model->tower, &model->tower.tiles[37], 225 + (15 * 3), 41 + (15 * 11));
    initialize_tile(&model->tower, &model->tower.tiles[38], 225 + (15 * 4), 41 + (15 * 11));
    initialize_tile(&model->tower, &model->tower.tiles[39], 225 + (15 * 5), 41 + (15 * 11));
    initialize_tile(&model->tower, &model->tower.tiles[40], 225 + (15 * 6), 41 + (15 * 11));
    initialize_tile(&model->tower, &model->tower.tiles[41], 225 + (15 * 7), 41 + (15 * 11));
    /*Row 13*/
    initialize_tile(&model->tower, &model->tower.tiles[42], 225, 41 + (15 * 12));
    initialize_tile(&model->tower, &model->tower.tiles[43], 225 + (15 * 2), 41 + (15 * 12));
    initialize_tile(&model->tower, &model->tower.tiles[44], 225 + (15 * 7), 41 + (15 * 12));
    initialize_tile(&model->tower, &model->tower.tiles[45], 225 + (15 * 9), 41 + (15 * 12));
    /*Row 14*/
    initialize_tile(&model->tower, &model->tower.tiles[46], 225 + 15, 41 + (15 * 13));
    initialize_tile(&model->tower, &model->tower.tiles[47], 225 + (15 * 2), 41 + (15 * 13));
    initialize_tile(&model->tower, &model->tower.tiles[48], 225 + (15 * 4), 41 + (15 * 13));
    initialize_tile(&model->tower, &model->tower.tiles[49], 225 + (15 * 5), 41 + (15 * 13));
    initialize_tile(&model->tower, &model->tower.tiles[50], 225 + (15 * 7), 41 + (15 * 13));
    initialize_tile(&model->tower, &model->tower.tiles[51], 225 + (15 * 8), 41 + (15 * 13));
    /*Row 15*/
    initialize_tile(&model->tower, &model->tower.tiles[52], 225 + (15 * 2), 41 + (15 * 14));
    initialize_tile(&model->tower, &model->tower.tiles[53], 225 + (15 * 3), 41 + (15 * 14));
    initialize_tile(&model->tower, &model->tower.tiles[54], 225 + (15 * 6), 41 + (15 * 14));
    initialize_tile(&model->tower, &model->tower.tiles[55], 225 + (15 * 7), 41 + (15 * 14));
    /*Row 16*/
    initialize_tile(&model->tower, &model->tower.tiles[56], 225, 41 + (15 * 15));
    initialize_tile(&model->tower, &model->tower.tiles[57], 225 + 15, 41 + (15 * 15));
    initialize_tile(&model->tower, &model->tower.tiles[58], 225 + (15 * 2), 41 + (15 * 15));
    initialize_tile(&model->tower, &model->tower.tiles[59], 225 + (15 * 7), 41 + (15 * 15));
    initialize_tile(&model->tower, &model->tower.tiles[60], 225 + (15 * 8), 41 + (15 * 15));
    initialize_tile(&model->tower, &model->tower.tiles[61], 225 + (15 * 9), 41 + (15 * 15));
    /*Row 17*/
    initialize_tile(&model->tower, &model->tower.tiles[62], 225 + 15, 41 + (15 * 16));
    initialize_tile(&model->tower, &model->tower.tiles[63], 225 + (15 * 3), 41 + (15 * 16));
    initialize_tile(&model->tower, &model->tower.tiles[64], 225 + (15 * 6), 41 + (15 * 16));
    initialize_tile(&model->tower, &model->tower.tiles[65], 225 + (15 * 8), 41 + (15 * 16));
    /*Row 18*/
    initialize_tile(&model->tower, &model->tower.tiles[66], 225, 41 + (15 * 17));
    initialize_tile(&model->tower, &model->tower.tiles[67], 225 + (15 * 4), 41 + (15 * 17));
    initialize_tile(&model->tower, &model->tower.tiles[68], 225 + (15 * 5), 41 + (15 * 17));
    initialize_tile(&model->tower, &model->tower.tiles[69], 225 + (15 * 9), 41 + (15 * 17));
    /*Row 19*/
    initialize_tile(&model->tower, &model->tower.tiles[70], 225 + (15 * 2), 41 + (15 * 18));
    initialize_tile(&model->tower, &model->tower.tiles[71], 225 + (15 * 3), 41 + (15 * 18));
    initialize_tile(&model->tower, &model->tower.tiles[72], 225 + (15 * 6), 41 + (15 * 18));
    initialize_tile(&model->tower, &model->tower.tiles[73], 225 + (15 * 7), 41 + (15 * 18));
    /*Row 20*/
    initialize_tile(&model->tower, &model->tower.tiles[74], 225 + 15, 41 + (15 * 19));
    initialize_tile(&model->tower, &model->tower.tiles[75], 225 + (15 * 4), 41 + (15 * 19));
    initialize_tile(&model->tower, &model->tower.tiles[76], 225 + (15 * 5), 41 + (15 * 19));
    initialize_tile(&model->tower, &model->tower.tiles[77], 225 + (15 * 8), 41 + (15 * 19));

    render(model, base_32, base_16, base_8);

    return 0;
}
