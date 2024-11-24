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
void clear_completed_rows(Field *playing_field, Tower *tower, Tetromino *active_piece);

/*Helper Functions*/
void adjust_position(Tetromino *active_piece, Field *playing_field);
void refresh_tower_tiles(Tower *tower, Field *playing_field);

#endif