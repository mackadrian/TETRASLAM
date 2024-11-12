#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"

/*Asynchronous Events*/
void move_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower, Direction direction);
void drop_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower);
void cycle_active_piece(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower);

/*Cascaded Events*/
void reset_active_piece(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower);
void clear_completed_rows(Tower *tower);

#endif