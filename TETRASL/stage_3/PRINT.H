#ifndef PRINT_H
#define PRINT_H

#include "model.h"

void print_model(Model *model);
void print_tetrominoes(Tetromino player_pieces[7]);
void print_playing_field(Field *playing_field);
void print_tower(Tower *tower);
void print_counter(Counter *counter);
void print_active_piece(Tetromino *player_piece);

#endif
