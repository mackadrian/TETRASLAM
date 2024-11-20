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
void wait_for_input();
void main_test_model();
void main_test_event(Model *model);
void test_initializer_tower_tiles(Model *model);
void test_initializer_active_piece(Model *model);
void test_move_event(Model *model);
void test_drop_event(Model *model);
void test_reset_active_piece_event(Model *model);
void test_cycle_event(Model *model);
void test_cycle_and_drop_event(Model *model);
void test_row_clear(Model *model);

int main()
{
    printf("\033E\033f\n");
    main_test_model();

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
    wait_for_input();

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
    wait_for_input();
    print_grid(&model.tower);

    wait_for_input();
    test_initializer_tower_tiles(&model);

    wait_for_input();
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
    test_move_event(model);
    /*
    test_reset_active_piece_event(model);

    test_cycle_event(model);

    test_cycle_and_drop_event(model);
    test_row_clear(model);*/
}

/*
----- FUNCTION: test_initializer_tower_tiles -----
Purpose: initializes all tiles of the tower and each of their position.
Assumptions: Tiles must be initialized inside the playing field.
*/
void test_initializer_tower_tiles(Model *model)
{
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
    wait_for_input();
    initialize_tetromino(&model->active_piece, 255, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);
    wait_for_input();
    printf("Re-initializing back to its original starting position.\n");
    initialize_tetromino(&model->active_piece, 285, 41, 16, 61, I_PIECE);
    print_active_piece(&model->active_piece);
}

/*
----- FUNCTION: test_move_event -----
Purpose: move the piece left or right with the specified key towards the playing field boundaries
*/
void test_move_event(Model *model)
{
    char key;
    printf("\n");
    printf("-- TESTING FOR LEFT/RIGHT OUT OF BOUNDS COLLISION --\n");
    printf("CURRENT ACTIVE PIECE POSITION: \n");
    print_active_piece(&model->active_piece);
    printf("Press 'n' OR 'N' key to move left.\n");
    printf("Press 'm' OR 'M' key to move right.\n");
    printf("Press 'SPACEBAR' key to drop the piece.\n");
    printf("Press ESC key to exit the loop.\n");

    while (TRUE)
    {
        key = Cnecin();

        if (key == 27)
        {
            printf("ESC key pressed. Exiting...\n");
            break;
        }

        if (key == 'n' || key == 'N')
        {
            move_left_request(&model->active_piece, &model->playing_field, &model->tower);
            printf("Moved Left: ");
            print_active_piece(&model->active_piece);
        }
        else if (key == 'm' || key == 'M')
        {
            move_right_request(&model->active_piece, &model->playing_field, &model->tower);
            printf("Moved Right: ");
            print_active_piece(&model->active_piece);
        }
        else if (key == ' ')
        {
            drop_request(&model->active_piece, &model->playing_field, &model->tower);
            printf("Dropped Piece: ");
            print_active_piece(&model->active_piece);
        }
    }
}

/*
----- FUNCTION: wait_for_input -----
Purpose: pauses execution until a key is pressed.
*/
void wait_for_input()
{
    while (!Cconis())
        ;
    Cnecin();
}