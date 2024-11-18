/**
 * @file LAYOUT.C
 * @brief contains all of the pieces' layout as an array.
 *        1 indicates a filled space and 0 is an empty space.
 * @author Mack Bautista
 */

#include "layout.h"

/*
----- LAYOUT: I_PIECE_LAYOUT -----
Purpose: Represents the layout for the I-shaped tetromino.
Details: - The piece consists of 4 blocks aligned vertically.
*/
const int I_PIECE_LAYOUT[PIECE_SIZE][PIECE_SIZE] = {
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0}};

/*
----- LAYOUT: J_PIECE_LAYOUT -----
Purpose: Represents the layout for the J-shaped tetromino.
Details: - The piece consists of 4 blocks forming a "J" shape.
*/
const int J_PIECE_LAYOUT[PIECE_SIZE][PIECE_SIZE] = {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}};

/*
----- LAYOUT: L_PIECE_LAYOUT -----
Purpose: Represents the layout for the L-shaped tetromino.
Details: - The piece consists of 4 blocks forming an "L" shape.
*/
const int L_PIECE_LAYOUT[PIECE_SIZE][PIECE_SIZE] = {
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}};

/*
----- LAYOUT: O_PIECE_LAYOUT -----
Purpose: Represents the layout for the O-shaped tetromino.
Details: - The piece consists of 4 blocks forming a square.
*/
const int O_PIECE_LAYOUT[PIECE_SIZE][PIECE_SIZE] = {
    {1, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};

/*
----- LAYOUT: S_PIECE_LAYOUT -----
Purpose: Represents the layout for the S-shaped tetromino.
Details: - The piece consists of 4 blocks forming an "S" shape.
*/
const int S_PIECE_LAYOUT[PIECE_SIZE][PIECE_SIZE] = {
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};

/*
----- LAYOUT: T_PIECE_LAYOUT -----
Purpose: Represents the layout for the T-shaped tetromino.
Details: - The piece consists of 4 blocks forming a "T" shape.
*/
const int T_PIECE_LAYOUT[PIECE_SIZE][PIECE_SIZE] = {
    {1, 1, 1, 0},
    {0, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};

/*
----- LAYOUT: Z_PIECE_LAYOUT -----
Purpose: Represents the layout for the Z-shaped tetromino.
Details: - The piece consists of 4 blocks forming a "Z" shape.
*/
const int Z_PIECE_LAYOUT[PIECE_SIZE][PIECE_SIZE] = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};

/*
----- LAYOUT: GRID_LAYOUT -----
Purpose:
    - Represents the default empty grid layout for the playing field.

Details:
     - The grid is a 2D array of zeros representing empty spaces.
     - Each cell can be updated with 1 to indicate occupied spaces.

Parameters:
    - (20x10) GRID_HEIGHT and GRID_WIDTH define the grid dimensions.

Limitations:
    - The dimensions must match the playing field configuration.
*/
int GRID_LAYOUT[GRID_HEIGHT][GRID_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};