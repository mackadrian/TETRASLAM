/**
 * @file T_MODEL.C
 * @brief tests the model by initializing snapshots of a hypothetical game session.
 * @author Mack Bautista
 */

#include "model.h"
#include "print.h"
#include <osbind.h>
#include <stdio.h>

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
    /*
    Cnecin();
    printf("\033E\033f\n");
    print_model(&testSnapshot);

    Print active piece
    Cnecin();
    printf("\033E\033f\n");
    print_active_piece(&testSnapshot.active_piece);

    Print player pieces
    Cnecin();
    printf("\033E\033f\n");
    print_tetrominoes(&testSnapshot.player_pieces);

    Print playing field
    Cnecin();
    printf("\033E\033f\n");
    print_playing_field(&testSnapshot.playing_field);

    Print tower and randomized tiles
    Cnecin();
    printf("\033E\033f\n");
    print_tower(&testSnapshot.tower);

    Print counter
    Cnecin();
    printf("\033E\033f\n");
    print_counter(&testSnapshot.counter);*/

    /*Move active piece to the left until collision is reached and then drop the active piece
    EXPECTED RESULT: - Collision with playing_field at (x,y) = 225,41 left boundary.
                     - Collision with playing_field at (x,y) = 225,282 bottom boundary.
    */
    Cnecin();
    printf("\033E\033f\n");
    while (!(testSnapshot.playing_field.collided))
    {
        move_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field, LEFT);
        print_active_piece(&testSnapshot.active_piece);
    }
    drop_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field,
                      &testSnapshot.tower);
    print_active_piece(&testSnapshot.active_piece);

    /* Reset player position in middle
    EXPECTED RESULT: - Position (x,y) = 285, 41.
                     - All flags reset to 0.
    */
    Cnecin();
    printf("\033E\033f\n");
    reset_active_pos(&testSnapshot.active_piece, &testSnapshot.playing_field, &testSnapshot.tower);
    print_active_piece(&testSnapshot.active_piece);

    /* Move active piece to the right until collision is reached and then drop the active piece
    EXPECTED RESULT: - Collision with playing_field at (x,y) = 360,41 right boundary.
                     - Collision with tower at tile position (x,y) = 360,131.
    */
    Cnecin();
    printf("\033E\033f\n");
    while (!(testSnapshot.playing_field.collided))
    {
        move_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field, RIGHT);
        print_active_piece(&testSnapshot.active_piece);
    }
    drop_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field,
                      &testSnapshot.tower);
    print_active_piece(&testSnapshot.active_piece);

    /*Reset player position in middle and then drop piece
    EXPECTED RESULT: - Position (x,y) = 285, 41.
                     - Collision with tower at tile_position (x,y) = 285,101.
    */
    Cnecin();
    printf("\033E\033f\n");
    reset_active_pos(&testSnapshot.active_piece, &testSnapshot.playing_field, &testSnapshot.tower);
    print_active_piece(&testSnapshot.active_piece);
    drop_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field,
                      &testSnapshot.tower);
    print_active_piece(&testSnapshot.active_piece);

    /* Reset player position, move to the right edge boundary, and cycle through pieces
        checking for out of bounds width and height.*/
    Cnecin();
    printf("\033E\033f\n");
    reset_active_pos(&testSnapshot.active_piece, &testSnapshot.playing_field, &testSnapshot.tower);
    print_active_piece(&testSnapshot.active_piece);
    while (!(testSnapshot.playing_field.collided))
    {
        move_active_piece(&testSnapshot.active_piece, &testSnapshot.playing_field, RIGHT);
        print_active_piece(&testSnapshot.active_piece);
    }
    cycle_active_piece(&testSnapshot.active_piece, testSnapshot.player_pieces, &testSnapshot.playing_field);
    print_active_piece(&testSnapshot.active_piece);

    return 0;
}