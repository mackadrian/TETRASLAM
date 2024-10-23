/**
 * @file T_MODEL.C
 * @brief tests the model by initializing snapshots of a hypothetical game session.
 * @author Mack Bautista
 */

#include "model.h"
#include "print.h"
#include <osbind.h>

/*DECLARATIONS*/
void initialize_model();

int main()
{
    initialize_model();

    return 0;
}

void initialize_model()
{
    int row, col;
    Model model;
    initialize_tetromino(&model.active_piece, 285, 41, 16, 61);
    initialize_tetromino(&model.player_pieces[0], 285, 41, 16, 61);
    initialize_tetromino(&model.player_pieces[1], 285, 41, 31, 46);
    initialize_tetromino(&model.player_pieces[2], 285, 41, 31, 46);
    initialize_tetromino(&model.player_pieces[3], 285, 41, 31, 31);
    initialize_tetromino(&model.player_pieces[4], 285, 41, 46, 31);
    initialize_tetromino(&model.player_pieces[5], 285, 41, 46, 31);
    initialize_tetromino(&model.player_pieces[6], 285, 41, 46, 31);

    initialize_field(&model.playing_field, 224, 40, 153, 303);
    initialize_tower(&model.tower, 285, 41, 151, 301, 9);
    initialize_counter(&model.counter, 224 + 153 + 32, 40, 100);

    initialize_tile(&model.tower.tiles[0], 255, 41 + (15 * 19));
    initialize_tile(&model.tower.tiles[1], 255 + 15, 41 + (15 * 19));
    initialize_tile(&model.tower.tiles[2], 255 + (15 * 2), 41 + (15 * 19));
    initialize_tile(&model.tower.tiles[3], 255 + (15 * 3), 41 + (15 * 19));
    initialize_tile(&model.tower.tiles[4], 255 + (15 * 4), 41 + (15 * 19));
    initialize_tile(&model.tower.tiles[5], 255 + (15 * 4), 41 + (15 * 19));
    initialize_tile(&model.tower.tiles[6], 255 + (15 * 5), 41 + (15 * 19));
    initialize_tile(&model.tower.tiles[7], 255 + (15 * 6), 41 + (15 * 19));
    initialize_tile(&model.tower.tiles[8], 255 + (15 * 7), 41 + (15 * 19));
    print_model(&model);
}
