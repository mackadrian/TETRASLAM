#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"
#include "types.h"

void handle_requests(Model *model, char *input);
void exit_request(char *input, bool *user_quit, bool *game_ended, bool *needs_render);

/*Asynchronous Events*/
void move_left_request(Tetromino *active_piece, Field *playing_field, Tower *tower);
void move_right_request(Tetromino *active_piece, Field *playing_field, Tower *tower);
void drop_request(Tetromino *active_piece, Field *playing_field, Tower *tower);
void cycle_active_piece(Tetromino *active_piece, Tetromino player_pieces[], Field *playing_field, Tower *tower);

/*Cascaded Events*/
void reset_active_piece(Tetromino *active_piece, Tetromino player_pieces[], Field *playing_field, Tower *tower);
void clear_completed_rows(Tower *tower);
bool recheck_full_rows(Tower *tower);

#endif