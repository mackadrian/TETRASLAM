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

void main_test_model();
void test_initializer_tower_tiles(Model *model);
void test_initializer_active_piece(Model *model);
void test_move_active_piece(Model *model);

int main()
{
    printf("\033E\033f\n");
    main_test_model();

    return 0;
}

/*
----- FUNCTION: main_test_model -----
Purpose: initializes model snapshot of the game
*/
void main_test_model()
{
    Model model;

    printf("Initializing model snapshot of TETRASLAM...\n Testing for successful initializtion...\n");
    printf("Tiles inside the tower should be blank...\n");
    Cnecin();

    initialize_tetromino(&model.active_piece, 285, 41, 16, 61);
    initialize_tetromino(&model.player_pieces[0], 285, 41, 16, 61);
    initialize_tetromino(&model.player_pieces[1], 285, 41, 31, 46);
    initialize_tetromino(&model.player_pieces[2], 285, 41, 31, 46);
    initialize_tetromino(&model.player_pieces[3], 285, 41, 31, 31);
    initialize_tetromino(&model.player_pieces[4], 285, 41, 46, 31);
    initialize_tetromino(&model.player_pieces[5], 285, 41, 46, 31);
    initialize_tetromino(&model.player_pieces[6], 285, 41, 46, 31);

    initialize_field(&model.playing_field, 224, 40, 153, 303);
    initialize_tower(&model.tower, 5);
    initialize_counter(&model.counter, 224 + 153 + 32, 40, 5);

    print_model(&model);

    Cnecin();
    test_initializer_tower_tiles(&model);

    Cnecin();
    test_initializer_active_piece(&model);

    Cnecin();
    test_move_active_piece(&model);
}

/*
----- FUNCTION: test_initializer_tower_tiles -----
Purpose: initializes all tiles of the tower and each of their position.
Assumptions: Tiles must be initialized inside the playing field.
*/
void test_initializer_tower_tiles(Model *model)
{
    printf("Initializing the tiles inside the tower structure...\n");
    printf("Tile 1: x=255, y=101 ==> R5 C1\n");
    printf("Tile 2: x=285, y=101 ==> R5 C3\n");
    printf("Tile 3: x=300, y=101 ==> R5 C4\n");
    printf("Tile 4: x=345, y=101 ==> R5 C9\n");
    printf("Tile 5: x=360, y=101 ==> R5 C10\n");
    initialize_tile(&model->tower.tiles[0], 255, 41 + (15 * 4));
    initialize_tile(&model->tower.tiles[1], 255 + (15 * 2), 41 + (15 * 4));
    initialize_tile(&model->tower.tiles[2], 255 + (15 * 3), 41 + (15 * 4));
    initialize_tile(&model->tower.tiles[3], 255 + (15 * 6), 41 + (15 * 4));
    initialize_tile(&model->tower.tiles[4], 255 + (15 * 7), 41 + (15 * 4));
    print_tower(&model->tower);
}

/*
----- FUNCTION: test_initializer_active_piece -----
Purpose: initializes the active piece at different columns
*/
void test_initializer_active_piece(Model *model)
{
    printf("Initializing a different position for the active piece.\n");
    Cnecin();
    initialize_tetromino(&model->active_piece, 255, 41, 16, 61);
    print_active_piece(&model->active_piece);
    Cnecin();
    printf("Re-initializing back to its original starting position.\n");
    initialize_tetromino(&model->active_piece, 285, 41, 16, 61);
    print_active_piece(&model->active_piece);
}

/*
----- FUNCTION: test_move_active_piece -----
Purpose: moves the active_piece towards the playing field boundaries
*/
void test_move_active_piece(Model *model)
{
    printf("-- TESTING FOR LEFT OUT OF BOUNDS COLLISION --\n");
    printf("Moving active piece to the left by 1 tile...\n");
    printf("Current (x,y) = 285, 41.\n");
    printf("Next tile at (x,y) = 270, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
    print_active_piece(&model->active_piece);
    Cnecin();
    printf("Moving active piece to the left by 1 tile...\n");
    printf("Current (x,y) = 270, 41.\n");
    printf("Next tile at (x,y) = 255, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
    print_active_piece(&model->active_piece);
    Cnecin();
    printf("Moving active piece to the left by 1 tile...\n");
    printf("Current (x,y) = 255, 41.\n");
    printf("Next tile at (x,y) = 240, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
    print_active_piece(&model->active_piece);
    Cnecin();
    printf("Moving active piece to the left by 1 tile...\n");
    printf("Current (x,y) = 240, 41.\n");
    printf("Next tile at (x,y) = 225, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
    print_active_piece(&model->active_piece);
    Cnecin();
    printf("Moving active piece outside of playing field boundary...\n");
    printf("Current (x,y) = 225, 41.\n");
    printf("Next tile at (x,y) = 225, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
    print_active_piece(&model->active_piece);
    Cnecin();
    printf("Moving the active piece again...\n");
    printf("Current (x,y) = 225, 41.\n");
    printf("Next tile at (x,y) = 225, 41.\n");
    move_active_piece(&model->active_piece, &model->playing_field, &model->tower, LEFT);
    print_active_piece(&model->active_piece);
}
