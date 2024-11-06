#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"

/*Asynchronous Events*/
void move_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower, Direction direction);
void drop_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower);
void cycle_active_piece(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower);

/*Cascaded Events*/
void reset_active_piece(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower);
void clear_completed_row(Tetromino *active_piece, Tower *tower);

bool check_row(Tower *tower, Tetromino *active_piece);
bool check_tiles_in_row(Tower *tower, unsigned int row);
unsigned int get_rows_to_check(Tetromino *active_piece);
#endif