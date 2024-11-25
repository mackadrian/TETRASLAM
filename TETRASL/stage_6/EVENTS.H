#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"
#include "types.h"

/*Asynchronous Events*/
void move_left_request(Tetromino *active_piece, Field *playing_field, Tower *tower);
void move_right_request(Tetromino *active_piece, Field *playing_field, Tower *tower);
void drop_request(Tetromino *active_piece, Field *playing_field, Tower *tower);
void cycle_active_piece(Tetromino *active_piece, Tetromino player_pieces[], Field *playing_field, Tower *tower);

/*Cascaded Events*/
void reset_active_piece(Tetromino *active_piece, Tetromino player_pieces[], Field *playing_field, Tower *tower);
void clear_completed_rows(Tower *tower, Tetromino *active_piece);
void shift_rows_down(Tower *tower, int cleared_row);
void clear_row(Tower *tower, int row);
int is_row_full(Tower *tower, int row);

#endif