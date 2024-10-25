#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"

/*Asynchronous Events*/
void move_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower, Direction direction);
/*
void drop_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower);
void reset_active_pos(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower);
void cycle_active_piece(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower);

void merge_active_piece_to_tower(Tetromino *active_piece, Tower *tower);*/

#endif