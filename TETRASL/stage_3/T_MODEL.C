/**
 * @file T_MODEL.C
 * @brief tests the model by initializing snapshots of a hypothetical game session.
 * @author Mack Bautista
 */

#include "model.h"
#include "print.h"
#include <osbind.h>

/* SNAPSHOT*/
Model testSnapshot = {
    /* default starting piece is the I_piece */
    {225 + (15 * 4), 41, 16, 61, MAX_TILES_PER_TETROMINO, 0, 0, 0},
    /* 7 tetrominoes for player */
    {
        {225 + (15 * 4), 41, 16, 61, MAX_TILES_PER_TETROMINO, 0, 0},
        {225 + (15 * 4), 41, 31, 46, MAX_TILES_PER_TETROMINO, 0, 0},
        {225 + (15 * 4), 41, 31, 46, MAX_TILES_PER_TETROMINO, 0, 0},
        {225 + (15 * 4), 41, 31, 31, MAX_TILES_PER_TETROMINO, 0, 0},
        {225 + (15 * 4), 41, 46, 31, MAX_TILES_PER_TETROMINO, 0, 0},
        {225 + (15 * 4), 41, 46, 31, MAX_TILES_PER_TETROMINO, 0, 0},
        {225 + (15 * 4), 41, 46, 31, MAX_TILES_PER_TETROMINO, 0, 0}},
    /* playing field */
    {224, 40, 153, 303, 100, 0, 0},
    /* tower */
    {
        225, 41, 151, 301, {
                               {225 + (15 * 7), 41 + (15 * 5), TILE_WIDTH, TILE_HEIGHT}, /* Tile 1 */
                               {225 + (15 * 7), 41 + (15 * 6), TILE_WIDTH, TILE_HEIGHT}, /* Tile 2 */
                               {225 + (15 * 8), 41 + (15 * 6), TILE_WIDTH, TILE_HEIGHT}, /* Tile 3 */
                               {225 + (15 * 9), 41 + (15 * 6), TILE_WIDTH, TILE_HEIGHT}, /* Tile 4 */
                               {225 + (15 * 1), 41 + (15 * 7), TILE_WIDTH, TILE_HEIGHT}, /* Tile 5 */
                               {225 + (15 * 2), 41 + (15 * 7), TILE_WIDTH, TILE_HEIGHT}, /* Tile 6 */
                               {225 + (15 * 3), 41 + (15 * 7), TILE_WIDTH, TILE_HEIGHT}, /* Tile 7 */
                               {225 + (15 * 4), 41 + (15 * 7), TILE_WIDTH, TILE_HEIGHT}, /* Tile 8 */
                               {225 + (15 * 9), 41 + (15 * 7), TILE_WIDTH, TILE_HEIGHT}, /* Tile 9 */
                               {225 + (15 * 6), 41 + (15 * 7), TILE_WIDTH, TILE_HEIGHT}  /* Tile 10 */
                           },
        10, /* Number of tiles in the tower */
        0},
    /* counter */
    {329 + (48 * 2), 40, 100}};

int main()
{
    int i;
    printf("\033E\033f\n");
    printf("Test 1: Printing initialized model snapshot... press any key to continue.\n");
    Cnecin();
    print_model(&testSnapshot);

    Cnecin();
    printf("\033E\033f\n");
    printf("Test 2: Given the first active piece: testing left playing field boundary collision... press any key to continue.\n");
    Cnecin();
    while (!(testSnapshot.playing_field.collided))
    {
        move_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field,
                          &testSnapshot.tower, LEFT);
        print_active_piece(&testSnapshot.active_piece);
    }
    printf("Drop the active piece to the left edge boundary... press any key to continue.\n");
    Cnecin();
    drop_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field,
                      &testSnapshot.tower);
    print_active_piece(&testSnapshot.active_piece);
    reset_active_pos(&testSnapshot.active_piece, testSnapshot.player_pieces,
                     &testSnapshot.playing_field, &testSnapshot.tower);

    Cnecin();
    printf("\033E\033f\n");
    printf("Test 3: Testing right playing field boundary collision... press any key to continue.\n");
    Cnecin();
    while (!(testSnapshot.playing_field.collided))
    {
        move_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field,
                          &testSnapshot.tower, RIGHT);
        print_active_piece(&testSnapshot.active_piece);
    }
    printf("Dropping the active piece to the right edge boundary... press any key to continue.\n");
    Cnecin();
    drop_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field,
                      &testSnapshot.tower);
    print_active_piece(&testSnapshot.active_piece);
    reset_active_pos(&testSnapshot.active_piece, testSnapshot.player_pieces,
                     &testSnapshot.playing_field, &testSnapshot.tower);

    Cnecin();
    printf("\033E\033f\n");
    printf("Test 5: Dropping active piece at the centre column... press any key to continue.\n");
    drop_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field,
                      &testSnapshot.tower);
    print_active_piece(&testSnapshot.active_piece);
    reset_active_pos(&testSnapshot.active_piece, testSnapshot.player_pieces,
                     &testSnapshot.playing_field, &testSnapshot.tower);

    Cnecin();
    printf("\033E\033f\n");
    printf("Test 6: Cycling active piece at the right edge boundary... press any key to continue.\n");
    Cnecin();
    while (!(testSnapshot.tower.collided))
    {
        move_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field,
                          &testSnapshot.tower, RIGHT);
        print_active_piece(&testSnapshot.active_piece);
    }
    printf("Cycling I-piece to J-piece... press any key to continue.\n");
    Cnecin();
    printf("\033E\033f\n");
    cycle_active_piece(&testSnapshot.active_piece, testSnapshot.player_pieces,
                       &testSnapshot.playing_field, &testSnapshot.tower);
    print_active_piece(&testSnapshot.active_piece);

    Cnecin();
    printf("\033E\033f\n");
    printf("Test 7: Cycling through all 7 pieces going back to I-piece... press any key to continue.\n");
    Cnecin();
    for (i = 0; i < 6; i++)
    {
        cycle_active_piece(&testSnapshot.active_piece, testSnapshot.player_pieces,
                           &testSnapshot.playing_field, &testSnapshot.tower);
        printf("Press any key to cycle to the next piece...\n");
        print_active_piece(&testSnapshot.active_piece);
        Cnecin();
    }

    return 0;
}