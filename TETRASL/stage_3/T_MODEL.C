/**
 * @file T_MODEL.C
 * @brief tests the model by initializing snapshots of a hypothetical game session.
 * @author Mack Bautista
 */

#include "model.h"
#include "print.h"
#include "events.h"
#include <stdio.h>
#include <osbind.h>

/*TEST DECLARATIONS*/
void main_test_model();
void main_test_event(Model *model);
void test_initializer_tower_tiles(Model *model);
void test_initializer_active_piece(Model *model);
void test_move_left_event(Model *model);
void test_move_right_event(Model *model);
void test_drop_event(Model *model);
void test_reset_active_piece_event(Model *model);
void test_cycle_event(Model *model);
void test_cycle_and_drop_event(Model *model);
void test_row_clear(Model *model);

int main()
{
    printf("\033E\033f\n");
    main_test_model();
    /*TODO: MORE TESTING*/

    return 0;
}

/*TEST BODIES*/
/*
----- FUNCTION: main_test_model -----
Purpose: initializes model snapshot of the game
*/
void main_test_model()
{
    Model model;

    printf("Initializing model snapshot of TETRASLAM...\n");
    printf("--- TESTING FOR SUCCESSFUL INITIALIZATION ---\n");
    printf("Tiles inside the tower should be blank...\n");
    Cnecin();

    initialize_tetromino(&model.active_piece, 285, 41, 16, 61, I_PIECE);
    initialize_tetromino(&model.player_pieces[0], 285, 41, 16, 61, I_PIECE);
    initialize_tetromino(&model.player_pieces[1], 285, 41, 31, 46, J_PIECE);
    initialize_tetromino(&model.player_pieces[2], 285, 41, 31, 46, L_PIECE);
    initialize_tetromino(&model.player_pieces[3], 285, 41, 31, 31, O_PIECE);
    initialize_tetromino(&model.player_pieces[4], 285, 41, 46, 31, S_PIECE);
    initialize_tetromino(&model.player_pieces[5], 285, 41, 46, 31, T_PIECE);
    initialize_tetromino(&model.player_pieces[6], 285, 41, 46, 31, Z_PIECE);

    initialize_field(&model.playing_field, 224, 40, 153, 303);
    initialize_tower(&model.tower, 8);
    initialize_counter(&model.counter, 224 + 153 + 32, 40, 8);

    print_model(&model);
    Cnecin();
    print_grid(&model.tower);

    Cnecin();
    test_initializer_tower_tiles(&model);

    Cnecin();
    test_initializer_active_piece(&model);

    /*Event testing*/
    main_test_event(&model);
}

/*
----- FUNCTION: main_test_event -----
Purpose: tests the events of model snapshot of the game
*/
void main_test_event(Model *model)
{
    Cnecin();
    test_move_left_event(model);
    Cnecin();
    test_move_right_event(model);
    Cnecin();
    test_drop_event(model);

    Cnecin();
    test_reset_active_piece_event(model);

    Cnecin();
    test_cycle_event(model);

    Cnecin();
    test_cycle_and_drop_event(model);
    Cnecin();
    test_row_clear(model);
}

/*
----- FUNCTION: test_initializer_tower_tiles -----
Purpose: initializes all tiles of the tower and each of their position.
Assumptions: Tiles must be initialized inside the playing field.
*/
void test_initializer_tower_tiles(Model *model)
{
    printf("\n");
    printf("Initializing the tiles inside the tower structure...\n");
    printf("Tile 1: x=255, y=101 ==> R5 C3\n");
    printf("Tile 2: x=285, y=101 ==> R5 C5\n");
    printf("Tile 3: x=300, y=101 ==> R5 C6\n");
    printf("Tile 4: x=345, y=101 ==> R5 C9\n");
    printf("Tile 5: x=360, y=101 ==> R5 C10\n");
    printf("Tile 6: x=270, y=101 ==> R5 C4\n");
    printf("Tile 7: x=330, y=101 ==> R5 C8\n");
    printf("Tile 8: x=315, y=101 ==> R5 C7\n");
    initialize_tile(&model->tower, &model->tower.tiles[0], 255, 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[1], 255 + (15 * 2), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[2], 255 + (15 * 3), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[3], 255 + (15 * 6), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[4], 255 + (15 * 7), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[5], 255 + 15, 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[6], 255 + (15 * 5), 41 + (15 * 4));
    initialize_tile(&model->tower, &model->tower.tiles[7], 255 + (15 * 4), 41 + (15 * 4));
    print_tower(&model->tower);
    print_grid(&model->tower);
    print_counter(&model->counter);
}

/*
----- FUNCTION: test_initializer_active_piece -----
Purpose: initializes the active piece at different columns
*/
void test_initializer_active_piece(Model *model)
{
    printf("\n");
    printf("Initializing a different position for the active piece.\n");
    Cnecin();
    initialize_tetromino(&model->active_piece, 255, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);
    Cnecin();
    printf("Re-initializing back to its original starting position.\n");
    initialize_tetromino(&model->active_piece, 285, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);
}

/*
----- FUNCTION: test_move_left_event -----
Purpose: moves the active_piece left towards the playing field boundaries
*/
void test_move_left_event(Model *model)
{
    printf("\n");
    printf("-- TESTING FOR LEFT OUT OF BOUNDS COLLISION --\n");
    printf("\n");
    printf("TEST 1: Moving active piece to the left by 1 tile...\n");
    printf("Current (x,y) = 285, 41.\n");
    printf("Next tile at (x,y) = 270, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
    print_active_piece(&model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 2: Moving active piece to the left by 1 tile...\n");
    printf("Current (x,y) = 270, 41.\n");
    printf("Next tile at (x,y) = 255, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
    print_active_piece(&model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 3: Moving active piece to the left by 1 tile...\n");
    printf("Current (x,y) = 255, 41.\n");
    printf("Next tile at (x,y) = 240, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
    print_active_piece(&model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 4: Moving active piece to the left by 1 tile...\n");
    printf("Current (x,y) = 240, 41.\n");
    printf("Next tile at (x,y) = 225, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
    print_active_piece(&model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 5: Moving active piece outside of playing field boundary...\n");
    printf("Current (x,y) = 225, 41.\n");
    printf("Next tile at (x,y) = 225, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
    print_active_piece(&model->active_piece);
    Cnecin();
}

/*
----- FUNCTION: test_move_right_event -----
Purpose: moves the active piece right towards the playing field boundaries
*/
void test_move_right_event(Model *model)
{
    printf("\n");
    printf("-- TESTING FOR RIGHT OUT OF BOUNDS COLLISION --\n");
    printf("Recentering active piece...\n");
    initialize_tetromino(&model->active_piece, 285, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 1: Moving active piece to the right by 1 tile...\n");
    printf("Current (x,y) = 285, 41.\n");
    printf("Next tile at (x,y) = 300, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, RIGHT);
    print_active_piece(&model->active_piece);

    printf("\n");
    Cnecin();
    printf("TEST 2: Moving active piece to the right by 1 tile...\n");
    printf("Current (x,y) = 300, 41.\n");
    printf("Next tile at (x,y) = 315, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, RIGHT);
    print_active_piece(&model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 3: Moving active piece to the right by 1 tile...\n");
    printf("Current (x,y) = 315, 41.\n");
    printf("Next tile at (x,y) = 330, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, RIGHT);
    print_active_piece(&model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 4: Moving active piece to the right by 1 tile...\n");
    printf("Current (x,y) = 330, 41.\n");
    printf("Next tile at (x,y) = 345, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, RIGHT);
    print_active_piece(&model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 5: Moving active piece to the right by 1 tile...\n");
    printf("Current (x,y) = 345, 41.\n");
    printf("Next tile at (x,y) = 360, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, RIGHT);
    print_active_piece(&model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 6: Moving active piece outside of the right playing field boundary...\n");
    printf("Current (x,y) = 360, 41.\n");
    printf("Next tile at (x,y) = 360, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, RIGHT);
    print_active_piece(&model->active_piece);
    Cnecin();
}

/*
----- FUNCTION: test_drop_event -----
Purpose: drops the active piece's y-position until it reaches a collision.
*/
void test_drop_event(Model *model)
{
    printf("\n");
    printf("-- TESTING FOR DROP COLLISION --\n");

    printf("\n");
    printf("TEST 1: DROPPING WITH TOWER COLLISION EXPECTED.\n");
    printf("Recentering active piece...\n");
    Cnecin();
    initialize_tetromino(&model->active_piece, 285, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);
    printf("\n");
    Cnecin();
    printf("Dropping at (x,y) = 285, 41...\n");
    printf("EXPECTED Collision with tower occurs at (x,y) = 285, 56.\n");
    printf("EXPECTED position at (x,y) = 285, 41.\n");
    drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 2: DROPPING WITH PLAYING FIELD COLLISION EXPECTED.\n");
    printf("Initializing at left boundary with no tower collision...\n");
    initialize_tetromino(&model->active_piece, 225, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);
    Cnecin();
    printf("\n");
    printf("Dropping at (x,y) = 225, 41...\n");
    printf("EXPECTED Collision with playing field occurs at (x,y) = 225, 194.\n");
    printf("EXPECTED position at (x,y) = 225, 281.\n");
    drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 3: DROPPING WITH TOWER COLLISION EXPECTED.\n");
    printf("Initializing at right boundary with tower collision...\n");
    initialize_tetromino(&model->active_piece, 360, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);
    printf("\n");
    Cnecin();
    printf("Dropping at (x,y) = 360, 41...\n");
    printf("EXPECTED Collision with tower occurs at (x,y) = 360, 56.\n");
    printf("EXPECTED position at (x,y) = 260, 41.\n");
    drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    Cnecin();
}

/*
----- FUNCTION: test_reset_active_piece_event -----
Purpose: test how the active piece becomes a part of the tower and resets to the original
          position
*/
void test_reset_active_piece_event(Model *model)
{
    printf("\n");
    printf("-- TESTING FOR MERGE WITH TOWER --\n");
    printf("SAME COLLISION TESTS AS TEST_MOVE_DROP_EVENT\n");
    printf("TILE COUNTER IS UPDATED ONCE ACTIVE PIECE RESETS.\n");

    printf("\n");
    printf("TEST 1: DROPPING WITH TOWER COLLISION EXPECTED.\n");
    printf("Recentering active piece...\n");
    initialize_tetromino(&model->active_piece, 285, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);
    printf("\n");
    Cnecin();
    printf("Dropping at (x,y) = 285, 41...\n");
    printf("EXPECTED Collision with tower occurs at (x,y) = 285, 56.\n");
    printf("EXPECTED position at (x,y) = 285, 41.\n");
    drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
    update_counter(&model->counter, &model->tower);
    print_tower(&model->tower);
    print_counter(&model->counter);
    Cnecin();

    printf("\n");
    printf("CALLING reset active piece position.\n");
    printf("EXPECTED position at (x,y) = 285, 41.\n");
    printf("EXPECTED tile count from 4 to 7.\n");
    reset_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    update_counter(&model->counter, &model->tower);
    print_tower(&model->tower);
    print_counter(&model->counter);
    Cnecin();
    print_grid(&model->tower);
    check_row_clearance(&model->tower, &model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 2: DROPPING WITH PLAYING FIELD COLLISION EXPECTED.\n");
    printf("Initializing at left boundary with no tower collision...\n");
    initialize_tetromino(&model->active_piece, 225, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);
    printf("\n");
    Cnecin();
    printf("Dropping at (x,y) = 225, 41...\n");
    printf("EXPECTED Collision with playing field occurs at (x,y) = 225, 194.\n");
    printf("EXPECTED position at (x,y) = 225, 281.\n");
    drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
    update_counter(&model->counter, &model->tower);
    print_tower(&model->tower);
    print_counter(&model->counter);
    Cnecin();

    printf("\n");
    printf("CALLING reset active piece position.\n");
    printf("EXPECTED position at (x,y) = 285, 41.\n");
    printf("EXPECTED tile count from 7 to 11.\n");
    reset_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    update_counter(&model->counter, &model->tower);
    print_tower(&model->tower);
    print_counter(&model->counter);
    Cnecin();
    print_grid(&model->tower);
    check_row_clearance(&model->tower, &model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 3: DROPPING WITH TOWER COLLISION EXPECTED.\n");
    printf("Initializing at right boundary with tower collision...\n");
    initialize_tetromino(&model->active_piece, 360, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);
    Cnecin();
    printf("\n");
    printf("Dropping at (x,y) = 260, 41...\n");
    printf("EXPECTED Collision with tower occurs at (x,y) = 360, 56.\n");
    printf("EXPECTED position at (x,y) = 260, 41.\n");
    drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
    update_counter(&model->counter, &model->tower);
    print_tower(&model->tower);
    print_counter(&model->counter);
    Cnecin();

    printf("\n");
    printf("CALLING reset active piece position.\n");
    printf("EXPECTED position at (x,y) = 285, 41.\n");
    printf("EXPECTED Updating tower tile count from 11 to 15.\n");
    reset_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    update_counter(&model->counter, &model->tower);
    print_tower(&model->tower);
    print_counter(&model->counter);
    Cnecin();
    print_grid(&model->tower);
    check_row_clearance(&model->tower, &model->active_piece);
    Cnecin();
}

/*
----- FUNCTION: test_cycle_event -----
Purpose: tests how the active piece is cycled
*/
void test_cycle_event(Model *model)
{
    printf("\n");
    printf("-- TESTING ACTIVE PIECE CYCLING --\n");

    printf("\n");
    printf("TEST 1: Cycle all pieces with no position adjustment.\n");
    printf("CYCLING I-piece to J-piece.\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("\n");
    printf("CYCLING J-piece to L-piece.\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING L-piece to O-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING O-piece to S-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING S-piece to T-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING T-piece to Z-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING Z-piece to I-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);

    printf("\n");
    printf("TEST 2: Testing for piece cycling at right boundary...\n");
    initialize_tetromino(&model->active_piece, 360, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);

    printf("\n");
    printf("CYCLING I-piece to J-piece.\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("\n");
    printf("CYCLING J-piece to L-piece.\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING L-piece to O-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING O-piece to S-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING S-piece to T-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING T-piece to Z-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING Z-piece to I-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);

    printf("\n");
    printf("TEST 3: Testing for piece cycling at left boundary...\n");
    initialize_tetromino(&model->active_piece, 225, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);

    printf("\n");
    printf("CYCLING I-piece to J-piece.\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("\n");
    printf("CYCLING J-piece to L-piece.\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING L-piece to O-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING O-piece to S-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING S-piece to T-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING T-piece to Z-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("CYCLING Z-piece to I-piece.\n");
    printf("\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
}

/*
----- FUNCTION: test_cycle_and_drop_event -----
Purpose: tests how the pieces that is not the I-piece interacts with collision
*/
void test_cycle_and_drop_event(Model *model)
{
    printf("\n");
    printf("-- TESTING DROP EVENT FOR PIECES THAT IS NOT I-PIECE --\n");

    printf("\n");
    printf("TEST 1: Drop J-piece at x: 225.\n");
    printf("EXPECTED Collision with tower occurs at (x,y)= 225, 281.\n");
    printf("EXPECTED Position at (x,y)= 225, 236.\n");
    Cnecin();
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    Cnecin();
    reset_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    update_counter(&model->counter, &model->tower);
    print_tower(&model->tower);
    print_counter(&model->counter);
    Cnecin();
    print_grid(&model->tower);
    check_row_clearance(&model->tower, &model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 2: Drop L-piece at x: 225.\n");
    printf("Recall to (x,y) = 225. 41.\n");
    initialize_tetromino(&model->active_piece, 225, 41, 16, 61, I_PIECE);
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("EXPECTED Collision with tower occurs at (x,y)= 225, 236.\n");
    printf("EXPECTED Position at (x,y)= 225, 191.\n");
    Cnecin();
    drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    Cnecin();
    reset_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    update_counter(&model->counter, &model->tower);
    print_tower(&model->tower);
    print_counter(&model->counter);
    Cnecin();
    print_grid(&model->tower);
    check_row_clearance(&model->tower, &model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 3: Drop O-piece at x: 225.\n");
    printf("Recall to (x,y) = 225. 41.\n");
    initialize_tetromino(&model->active_piece, 225, 41, 16, 61, I_PIECE);
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("EXPECTED Collision with tower occurs at (x,y)= 225, 191.\n");
    printf("EXPECTED Position at (x,y)= 225, 161.\n");
    Cnecin();
    drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    Cnecin();
    reset_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    update_counter(&model->counter, &model->tower);
    print_tower(&model->tower);
    print_counter(&model->counter);
    Cnecin();
    print_grid(&model->tower);
    check_row_clearance(&model->tower, &model->active_piece);
    Cnecin();

    printf("\n");
    printf("TEST 4: Drop O-piece at x: 225.\n");
    printf("Recall to (x,y) = 225. 41.\n");
    initialize_tetromino(&model->active_piece, 225, 41, 16, 61, I_PIECE);
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("EXPECTED Collision with tower occurs at (x,y)= 225, 161.\n");
    printf("EXPECTED Position at (x,y)= 225, 101.\n");
    Cnecin();
    drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    Cnecin();
    reset_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    update_counter(&model->counter, &model->tower);
    print_tower(&model->tower);
    print_counter(&model->counter);
    Cnecin();
    print_grid(&model->tower);
    check_row_clearance(&model->tower, &model->active_piece);
    Cnecin();
}

/*
----- FUNCTION: test_cycle_and_drop_event -----
Purpose: tests how rows are cleared when all columns have adjacent connecting tiles
*/
void test_row_clear(Model *model)
{
    printf("\n");
    printf("-- TESTING FOR ROW CLEAR --\n");

    printf("\n");
    printf("TEST 5: Drop O-piece at x: 225.\n");
    printf("Recall to (x,y) = 225. 41.\n");
    initialize_tetromino(&model->active_piece, 225, 41, 16, 61, I_PIECE);
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    printf("EXPECTED Collision with tower occurs at (x,y)= 225, 101.\n");
    printf("EXPECTED Position at (x,y)= 225, 71.\n");
    Cnecin();
    drop_active_piece(&model->active_piece, &model->playing_field, &model->tower);
    print_active_piece(&model->active_piece);
    Cnecin();
    reset_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
    update_counter(&model->counter, &model->tower);
    Cnecin();
    print_tower(&model->tower);
    Cnecin();
    print_counter(&model->counter);
    Cnecin();
    print_grid(&model->tower);

    printf("\n");
    printf("CALLING clear_completed_rows.\n");
    Cnecin();
    clear_completed_rows(&model->tower, &model->active_piece);
    update_grid(&model->tower);
    print_grid(&model->tower);

    printf("\n");
    printf("UPDATING TILES AND PRINTING UPDATED TILES...\n");
    Cnecin();
    update_tiles(&model->tower);
    update_counter(&model->counter, &model->tower);
    print_counter(&model->counter);
    Cnecin();
    print_tower(&model->tower);

    Cnecin();
}