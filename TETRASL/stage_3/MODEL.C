/**
 * @file MODEL.C
 * @brief contains all of TETRASLAM's object behaviour functions.
 * @author Mack Bautista
 */

#include "model.h"
#include "layout.h"
#include <stdio.h>

/*
----- FUNCTION: initialize_tower -----
Purpose: Initializes the tower structure, setting its grid layout and calculating the tile count.

Parameters:
    - Field *playing_field: Pointer to the playing field structure (currently unused).
    - Tower *new_tower: Pointer to the tower structure to initialize.

Limitations:
    - Assumes tiles and grid layout (e.g., 'GRID_LAYOUT') are predefined and available.
    - Positions of tiles are set to default values and may require further adjustment based on gameplay mechanics (e.g., piece placement, collisions).
    - The 'max_row' will reflect the highest occupied row in the grid, which is relevant for piece placement and collision detection.

Returns:
    - None. The function directly modifies the 'new_tower' structure.
*/
void initialize_tower(Tower *new_tower, int layout[GRID_HEIGHT][GRID_WIDTH])
{
    unsigned int row, col;
    new_tower->is_row_full = 0;
    new_tower->max_row = 0;
    new_tower->tile_count = 0;

    initialize_grid(new_tower, layout);

    for (row = 0; row < GRID_HEIGHT; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            if (new_tower->grid[row][col] == 1)
            {
                new_tower->tile_count++;
            }
        }
    }
}

/*
----- FUNCTION: initialize_grid -----
Purpose: Initializes the grid in the tower structure using a predefined layout.

Parameters:
    - Model *model: Pointer to the model structure that holds the tower.
    - const int layout[GRID_HEIGHT][GRID_WIDTH]: A 2D array representing the desired grid layout to initialize the tower grid.

Limitations:
    - Assumes the provided 'layout' array is valid and matches the size of the tower grid.
    - The layout array must be defined before calling this function.

Returns:
    - None. The function directly modifies the 'model->tower.grid' based on the given layout.
*/
void initialize_grid(Tower *new_tower, int layout[GRID_HEIGHT][GRID_WIDTH])
{
    int x, y;
    for (y = 0; y < GRID_HEIGHT; y++)
    {
        for (x = 0; x < GRID_WIDTH; x++)
        {
            new_tower->grid[y][x] = layout[y][x];
        }
    }
}

/*
----- FUNCTION: initialize_layout -----
Purpose: initializes the tetromino layout based on its type.

Details:
    - Assigns a predefined layout (e.g., I_PIECE_LAYOUT) to the new tetromino based on its type.
    - The layout is represented as a 2D array of size 4x4.

Parameters:
    - Tetromino *new_tetromino: pointer to the tetromino being initialized.
    - TetrominoType type: the type of the tetromino (e.g., I_PIECE, T_PIECE).

Limitations:
    - Assumes the layouts (e.g., I_PIECE_LAYOUT) are predefined and accessible.
    - Does not handle invalid or undefined types.
*/
void initialize_layout(Tetromino *new_tetromino, TetrominoType type)
{
    unsigned int i, j;
    const int(*layout)[PIECE_SIZE] = NULL;

    switch (type)
    {
    case I_PIECE:
        new_tetromino->layout = I_PIECE_LAYOUT;
        break;
    case J_PIECE:
        new_tetromino->layout = J_PIECE_LAYOUT;
        break;
    case L_PIECE:
        new_tetromino->layout = L_PIECE_LAYOUT;
        break;
    case O_PIECE:
        new_tetromino->layout = O_PIECE_LAYOUT;
        break;
    case S_PIECE:
        new_tetromino->layout = S_PIECE_LAYOUT;
        break;
    case T_PIECE:
        new_tetromino->layout = T_PIECE_LAYOUT;
        break;
    case Z_PIECE:
        new_tetromino->layout = Z_PIECE_LAYOUT;
        break;
    default:
        return;
    }
}

/*
----- FUNCTION: initialize_tetromino -----
Purpose: initializes a tetromino by setting its properties and assigning its layout.

Details:
    - Sets the initial position, dimensions, velocities, and state flags of the tetromino.
    - Assigns a predefined layout based on the tetromino's type using the initialize_layout function.

Parameters:
    - Tetromino *new_tetromino: pointer to the tetromino being initialized.
    - unsigned int x: x-coordinate of the tetromino.
    - unsigned int y: y-coordinate of the tetromino.
    - unsigned int width: width of the tetromino.
    - unsigned int height: height of the tetromino.
    - TetrominoType type: the type of the tetromino (e.g., I_PIECE, T_PIECE).

Limitations:
    - Assumes the velocity values are fixed at 16 (CONST_VELOCITY).
    - Assumes 4 (MAX_TILES_PER_TETROMINO) is correctly defined for tile_count.
*/
void initialize_tetromino(Tetromino *new_tetromino, unsigned int x, unsigned int y, unsigned int width, unsigned int height, TetrominoType type)
{
    new_tetromino->x = x;
    new_tetromino->y = y;
    new_tetromino->width = width;
    new_tetromino->height = height;
    new_tetromino->tile_count = MAX_TILES_PER_TETROMINO;
    new_tetromino->curr_index = 0;
    new_tetromino->velocity_x = CONST_VELOCITY;
    new_tetromino->velocity_y = CONST_VELOCITY;
    new_tetromino->merged = FALSE;
    new_tetromino->dropped = FALSE;

    initialize_layout(new_tetromino, type);
}

/*
----- FUNCTION: initialize_field -----
Purpose: Initializes the playing field, setting its position and dimensions.

Parameters:
    - Field *new_field: Pointer to the field structure to initialize.
    - unsigned int x: X-coordinate of the field.
    - unsigned int y: Y-coordinate of the field.
    - unsigned int width: Width of the field in pixels.
    - unsigned int height: Height of the field in pixels.

Limitations:
    - The playing field must be defined within the boundaries of the game window.
*/
void initialize_field(Field *new_field, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    new_field->x = x;
    new_field->y = y;
    new_field->width = width;
    new_field->height = height;
}

/*
----- FUNCTION: initialize_counter -----
Purpose: Initializes the counter used to track the number of tiles in the tower.

Parameters:
    - Counter *new_counter: Pointer to the counter structure to initialize.
    - unsigned int x: X-coordinate of the counter.
    - unsigned int y: Y-coordinate of the counter.
    - int tile_count: Initial tile count to set in the counter.
*/
void initialize_counter(Counter *new_counter, Tower *tower, unsigned int x, unsigned int y)
{
    new_counter->x = x;
    new_counter->y = y;
    new_counter->tile_count = tower->tile_count;
}

/*
----- FUNCTION: cycle_piece_layout -----
Purpose: returns the layout corresponding to the current piece's index.

Details:
    - The function maps a piece's index (0-6) to its corresponding predefined layout.
    - Each piece has a unique layout defined as a 2D array with size PIECE_SIZE x PIECE_SIZE.
    - If an invalid index is passed, the function returns NULL.

Parameters:
    - int curr_index: the current piece's index, ranging from 0 to 6, corresponding to specific tetrominoes:
        0 -> I_PIECE_LAYOUT
        1 -> J_PIECE_LAYOUT
        2 -> L_PIECE_LAYOUT
        3 -> O_PIECE_LAYOUT
        4 -> S_PIECE_LAYOUT
        5 -> T_PIECE_LAYOUT
        6 -> Z_PIECE_LAYOUT

Return:
    - const int (*)[PIECE_SIZE]: a pointer to a 2D array representing the layout of the tetromino.
      - Returns NULL if an invalid index is provided.

Limitations:
    - The function does not validate curr_index for being out of bounds (e.g., < 0 or > 6).
    - Assumes PIECE_SIZE is defined and corresponds to the size of the layout arrays.
    - The layouts (e.g., I_PIECE_LAYOUT, J_PIECE_LAYOUT) must be properly defined and accessible in the same scope.
*/
const int (*cycle_piece_layout(int curr_index))[PIECE_SIZE]
{
    switch (curr_index)
    {
    case 0:
        return I_PIECE_LAYOUT;
    case 1:
        return J_PIECE_LAYOUT;
    case 2:
        return L_PIECE_LAYOUT;
    case 3:
        return O_PIECE_LAYOUT;
    case 4:
        return S_PIECE_LAYOUT;
    case 5:
        return T_PIECE_LAYOUT;
    case 6:
        return Z_PIECE_LAYOUT;
    default:
        return NULL;
    }
}

/*
----- FUNCTION: get_grid_coordinates -----
Purpose: converts the (x, y) pixel coordinates into grid coordinates to be used
         within the grid layout.

Details:
    - This function calculates the grid coordinates (grid_x, grid_y) based on the provided pixel coordinates (x, y).
    - The conversion formula assumes that the grid layout starts at a fixed offset (FIELD_X_OFFSET, FIELD_Y_OFFSET) and uses a constant cell size defined by CONST_VELOCITY.

Parameters:
    - unsigned int x: the x-coordinate in pixels.
    - unsigned int y: the y-coordinate in pixels.
    - unsigned int *grid_x: pointer to store the calculated grid x-coordinate.
    - unsigned int *grid_y: pointer to store the calculated grid y-coordinate.

Formula:
    grid_x = (224 - x) / 16
    grid_y = (32 - y) / 16

Limitations:
    - Assumes the playing field starts at (x, y) = (220, 40).
    - Assumes CONST_VELOCITY is a divisor of the pixel dimensions.
    - No boundary checks on the resulting grid coordinates.
*/
void get_grid_coordinates(Field *playing_field,
                          unsigned int x, unsigned int y,
                          unsigned int *grid_x, unsigned int *grid_y)
{
    *grid_x = (x - playing_field->x) >> PIECE_SIZE;
    *grid_y = (y - playing_field->y) >> PIECE_SIZE;
}

/*
----- FUNCTION: move_active_piece_left -----
Purpose:
    - Moves the active player-controlled tetromino to the left by updating its x-coordinate.

Details:
    - This function decreases the x-coordinate of the active tetromino by its velocity in the x-direction.
    - The amount by which the tetromino moves is determined by the value of 'velocity_x', which can be adjusted for different movement speeds.

Parameters:
    - Tetromino *active_piece: Pointer to the active tetromino structure, which contains the x-coordinate and velocity.

Limitations:
    - Assumes that the 'velocity_x' value has been properly initialized for the active tetromino.
    - Does not check for boundary conditions or collisions; those must be handled separately.
*/
void move_active_piece_left(Tetromino *active_piece)
{
    active_piece->x -= active_piece->velocity_x;
}

/*
----- FUNCTION: move_active_piece_right -----
Purpose:
    - Moves the active player-controlled tetromino to the right by updating its x-coordinate.

Details:
    - This function increases the x-coordinate of the active tetromino by its velocity in the x-direction.
    - The amount by which the tetromino moves is determined by the value of 'velocity_x', which can be adjusted for different movement speeds.

Parameters:
    - Tetromino *active_piece: Pointer to the active tetromino structure, which contains the x-coordinate and velocity.

Limitations:
    - Assumes that the 'velocity_x' value has been properly initialized for the active tetromino.
    - Does not check for boundary conditions or collisions; those must be handled separately.
*/
void move_active_piece_right(Tetromino *active_piece)
{
    active_piece->x += active_piece->velocity_x;
}

/*
----- FUNCTION: drop_active_piece -----
Purpose:
    - Moves the active player-controlled tetromino downward by updating its y-coordinate.

Details:
    - This function increases the y-coordinate of the active tetromino by its velocity in the y-direction.
    - The amount by which the tetromino moves downward is determined by the value of 'velocity_y', which can be adjusted for different movement speeds.

Parameters:
    - Tetromino *active_piece: Pointer to the active tetromino structure, which contains the y-coordinate and velocity.

Limitations:
    - Assumes that the 'velocity_y' value has been properly initialized for the active tetromino.
    - Does not check for boundary conditions or collisions with the bottom of the playing field or other pieces; those must be handled separately.
*/
void drop_active_piece(Tetromino *active_piece)
{
    active_piece->y += active_piece->velocity_y;
}

/*
----- FUNCTION: update_tower -----
Purpose:
    - Updates the tower by merging the active piece into the tower and adjusting the tower's state.

Details:
    - Merges the active piece's layout into the tower grid and tile array.
    - Adjusts the merged state of the active piece to indicate it is no longer active.

Parameters:
    - Tetromino *active_piece: Pointer to the currently active piece.
    - Tower *tower: Pointer to the tower structure.

Limitations:
    - Assumes active_piece and tower are initialized and valid.
    - The active piece must have a defined layout.
*/
void update_tower(Field *playing_field, Tetromino *active_piece, Tower *tower)
{
    unsigned int i, j;
    unsigned int grid_x, grid_y;

    active_piece->merged = FALSE;

    for (i = 0; i < PIECE_SIZE; i++)
    {
        for (j = 0; j < PIECE_SIZE; j++)
        {
            if (active_piece->layout[i][j] == 1)
            {
                get_grid_coordinates(playing_field, active_piece->x + (j * CONST_VELOCITY),
                                     active_piece->y + (i * CONST_VELOCITY),
                                     &grid_x, &grid_y);

                if (grid_x >= 0 && grid_x < GRID_WIDTH && grid_y >= 0 && grid_y < GRID_HEIGHT)
                {
                    tower->grid[grid_y][grid_x] = 1;
                    tower->max_row = grid_y;
                }
            }
        }
    }
}

/*
----- FUNCTION: update_counter -----
Purpose:
    - Updates the counter to reflect the current tile count from the tower.

Details:
    - Sets the 'tile_count' of the 'counter' to match the 'tile_count' of the 'tower'.
    - This ensures the counter displays the correct number of tiles in the tower at any given moment.

Parameters:
    - Counter *counter: Pointer to the counter structure that tracks the tile count.
    - Tower *tower: Pointer to the tower structure containing the current tile count.

Limitations:
    - Assumes the 'counter' and 'tower' structures are initialized and valid.
    - Only updates the 'tile_count' field of the 'counter'; no other tower-related state is modified.
*/
void update_counter(Counter *counter, Tower *tower)
{
    unsigned int i, j;
    unsigned int filled_tile_count = 0;

    for (i = 0; i < GRID_HEIGHT; i++)
    {
        for (j = 0; j < GRID_WIDTH; j++)
        {
            if (tower->grid[i][j] == 1)
            {
                filled_tile_count++;
            }
        }
    }

    tower->tile_count = filled_tile_count;
    counter->tile_count = filled_tile_count;
}

/*
----- FUNCTION: player_bounds_collision -----
Purpose:
    - Checks if the active piece has moved outside the playing field boundaries.

Details:
    - Compares the active piece's coordinates with the playing field's dimensions.
    - Identifies out-of-bounds movement and one can only be checked one at a time.
    - Player cannot move the active piece once it is dropped.

Parameters:
    - Tetromino *active_piece: Pointer to the active piece.
    - Field *playing_field: Pointer to the playing field structure.

Return:
    - bool: TRUE if out of bounds, FALSE otherwise.

Limitations:
    - Assumes active piece and playing field are initialized.
    - Does not account for velocity or future positions.
*/
bool player_bounds_collision(Tetromino *active_piece, Field *playing_field)
{
    bool has_collided = FALSE;
    if (active_piece->x < playing_field->x ||
        active_piece->x + active_piece->width > playing_field->x + playing_field->width)
    {
        has_collided = TRUE;
    }

    if (active_piece->y < playing_field->y ||
        active_piece->y + active_piece->height > playing_field->y + playing_field->height)
    {
        has_collided = TRUE;
    }

    return has_collided;
}

/*
----- FUNCTION: tower_collision -----
Purpose:
    - Checks if the active piece has collided with any tiles in the tower.

Details:
    - Efficiently checks only the filled blocks of the active piece's layout.
    - Reduces the number of comparisons by checking against only relevant tiles.

Parameters:
    - Tetromino *active_piece: Pointer to the active piece.
    - Tower *tower: Pointer to the tower structure.

Return:
    - bool: TRUE if a collision occurs, FALSE otherwise.
*/
bool tower_collision(Tetromino *active_piece, Tower *tower, Field *playing_field)
{
    unsigned int i, j;
    unsigned int tile_x, tile_y;
    unsigned int grid_x, grid_y;

    for (i = 0; i < PIECE_SIZE; i++)
    {
        for (j = 0; j < PIECE_SIZE; j++)
        {
            if (active_piece->layout[i][j] == 1)
            {

                tile_x = active_piece->x + (j * CONST_VELOCITY);
                tile_y = active_piece->y + (i * CONST_VELOCITY);

                get_grid_coordinates(playing_field, tile_x, tile_y, &grid_x, &grid_y);

                if (grid_x < GRID_WIDTH && grid_y < GRID_HEIGHT)
                {
                    if (tower->grid[grid_y][grid_x] == 1)
                    {
                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

/*
----- FUNCTION: fatal_tower_collision -----
Purpose:
    - Checks if the tower has reached the top of the playing field, indicating a loss condition.

Details:
    - Scans the top row of the tower grid for any occupied cells.
    - Returns TRUE if any cell is occupied.

Parameters:
    - Tower *tower: Pointer to the tower structure.

Return:
    - bool: TRUE if a collision with the top row occurs, FALSE otherwise.

Limitations:
    - Assumes the grid's top row is accessible.
    - Does not account for partial rows beyond the visible grid.
*/
bool fatal_tower_collision(Tower *tower)
{
    int col;

    for (col = 0; col < GRID_WIDTH; col++)
    {
        if (tower->grid[0][col] != 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*
----- FUNCTION: win_condition -----
Purpose:
    - Checks if the tower's tile count meets a specific threshold to determine a win condition.

Details:
    - Compares the tower's current tile count to a defined winning threshold.
    - Returns TRUE if the current tile count meets or exceeds the threshold.
    - Returns FALSE if the tile count does not meet the threshold.

Parameters:
    - Tower *tower: Pointer to the tower structure that contains the tile count.

Returns:
    - TRUE if the tower's tile count meets or exceeds the threshold.
    - FALSE otherwise.
*/
bool win_condition(Tower *tower)
{
    if (tower->tile_count == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*
----- FUNCTION: check_row -----
Purpose:
    - Checks if the specified rows in the tower are completely filled with tiles and updates relevant variables accordingly.

Details:
    - Scans the rows in the tower grid from 'max_row' down to 'min_row' (calculated based on the height of the active piece) to determine if all columns in a row are occupied.
    - If a row is full, the 'is_row_full' counter is incremented and 'max_row' is updated to the first fully completed row.
    - The function checks each row's columns and determines if all cells are filled. If any empty space is found in the row, it moves to the next row without updating the counter or 'max_row'.

Parameters:
    - Tower *tower: Pointer to the tower structure containing the grid, 'max_row', and 'is_row_full' counter.
    - Tetromino *active_piece: Pointer to the active piece being dropped, which helps in determining the row range to check based on its height.

Limitations:
    - Assumes the row index is within valid bounds of the tower grid (i.e., 0 <= row < GRID_HEIGHT).
    - Only checks for completely filled rows and does not handle partially filled rows or invalid grid configurations.
    - The 'max_row' is updated only to the first fully completed row; this ensures that the game keeps track of the highest filled row for further processing.
*/
void check_row(Tower *tower, Tetromino *active_piece)
{
    int row, col;
    bool is_full = TRUE;

    int min_row = tower->max_row - (active_piece->height >> PIECE_SIZE);

    if (min_row < 0)
    {
        min_row = 0;
    }

    for (row = tower->max_row; row >= min_row; row--)
    {

        is_full = TRUE;

        for (col = 0; col < GRID_WIDTH; col++)
        {
            if (tower->grid[row][col] == 0)
            {
                is_full = FALSE;
                break;
            }
        }

        if (is_full)
        {
            tower->is_row_full++;
            tower->max_row = row;
        }
    }
}
