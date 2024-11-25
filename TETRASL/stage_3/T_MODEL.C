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
void test_move_event(Model *model);

int test_layout[GRID_HEIGHT][GRID_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
    {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {0, 1, 1, 0, 1, 1, 0, 1, 1, 0},
    {0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
    {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0}};

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
    wait_for_input();

    initialize_tetromino(&model.active_piece, 288, 32, 16, 64, I_PIECE);
    initialize_tetromino(&model.player_pieces[0], 288, 32, 16, 64, I_PIECE);
    initialize_tetromino(&model.player_pieces[1], 288, 32, 32, 46, J_PIECE);
    initialize_tetromino(&model.player_pieces[2], 288, 32, 32, 46, L_PIECE);
    initialize_tetromino(&model.player_pieces[3], 288, 32, 32, 32, O_PIECE);
    initialize_tetromino(&model.player_pieces[4], 288, 32, 48, 32, S_PIECE);
    initialize_tetromino(&model.player_pieces[5], 288, 32, 48, 32, T_PIECE);
    initialize_tetromino(&model.player_pieces[6], 288, 32, 48, 32, Z_PIECE);

    initialize_field(&model.playing_field, 224, 32, 160, 320);
    initialize_tower(&model.tower, test_layout);
    initialize_counter(&model.counter, &model.tower, 384 + 16, 32);

    print_model(&model);
    print_grid(&model.tower);

    /*Event testing*/
    main_test_event(&model);
}

/*
----- FUNCTION: main_test_event -----
Purpose: tests the events of model snapshot of the game
*/
void main_test_event(Model *model)
{
    char key;
    printf("\n");
    printf("-- TESTING FOR LEFT/RIGHT OUT OF BOUNDS COLLISION --\n");
    printf("CURRENT ACTIVE PIECE POSITION: \n");
    print_active_piece(&model->active_piece);
    printf("Press 'c' OR 'C' key to cycle active piece.\n");
    printf("Press 'n' OR 'N' key to move left.\n");
    printf("Press 'm' OR 'M' key to move right.\n");
    printf("Press 'SPACEBAR' key to drop the piece.\n");
    printf("Press 'q' OR 'Q' key to print the grid.\n");
    printf("Press ESC key to exit the loop.\n");

    while (TRUE)
    {
        key = Cnecin();

        if (key == 27)
        {
            printf("ESC key pressed. Exiting...\n");
            break;
        }

        else if (key == 'c' || key == 'C')
        {
            cycle_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
            printf("New cycled active piece: ");
            print_active_piece(&model->active_piece);
        }
        else if (key == 'n' || key == 'N')
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

            check_row(&model->tower, &model->active_piece);
            reset_active_piece(&model->active_piece, &model->player_pieces, &model->playing_field, &model->tower);
            update_counter(&model->counter, &model->tower);
            print_grid(&model->tower);

            print_counter(&model->counter);
            print_tower(&model->tower);

            if (fatal_tower_collision(&model->tower))
            {
                printf("GAME OVER!! Exiting...\n");
                break;
            }
        }
        else if (key == 'q' || key == 'Q')
        {
            printf("Current Grid:\n");
            print_grid(&model->tower);
        }

        if (model->tower.is_row_full > 0)
        {
            clear_completed_rows(&model->tower);
            update_counter(&model->counter, &model->tower);
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