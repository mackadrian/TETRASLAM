/**
 * @file MODEL.C
 * @brief contains all of TETRASLAM's object behaviour functions.
 * @author Mack Bautista
 */

#include "model.h"
#include "layout.h"
#include <stdio.h>

#define OFFSET 1
#define CONST_VELOCITY 15

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
    grid_x = (x - 225) / 15
    grid_y = (y - 41) / 15

Limitations:
    - Assumes the playing field starts at (x, y) = (220, 40).
    - Assumes CONST_VELOCITY is a divisor of the pixel dimensions.
    - No boundary checks on the resulting grid coordinates.
*/
void get_grid_coordinates(unsigned int x, unsigned int y,
                          unsigned int *grid_x, unsigned int *grid_y)
{
    *grid_x = (x - 225) / 15;
    *grid_y = (y - 41) / 15;
}

/*
----- FUNCTION: initialize_tile -----
Purpose: initializes a tile by setting its position, dimensions, and updating the tower grid.

Details:
    - The tile's position is defined by (x, y), and its size is fixed at TILE_WIDTH x TILE_HEIGHT.
    - The function also updates the tower's grid representation if the tile lies within the grid bounds.

Parameters:
    - Tower *tower: pointer to the tower structure, containing the grid.
    - Tile *new_tile: pointer to the tile being initialized.
    - unsigned int x: x-coordinate of the tile.
    - unsigned int y: y-coordinate of the tile.

Limitations:
    - Assumes all tiles are 16x16 in size.
    - Does not handle cases where the tile falls outside the tower's grid dimensions.
*/
void initialize_tile(Tower *tower, Tile *new_tile, unsigned int x, unsigned int y)
{
    unsigned int grid_x, grid_y;

    new_tile->x = x;
    new_tile->y = y;
    new_tile->width = TILE_WIDTH;
    new_tile->height = TILE_HEIGHT;

    get_grid_coordinates(x, y, &grid_x, &grid_y);
    if (grid_x >= 0 && grid_x < 10 && grid_y >= 0 && grid_y < 20)
    {
        tower->grid[grid_y][grid_x] = 1;
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
    - Assumes the velocity values are fixed at 15 (CONST_VELOCITY).
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
----- FUNCTION: initialize_tower -----
Purpose: Initializes the tower structure, setting its tiles and grid layout.

Parameters:
    - Tower *new_tower: Pointer to the tower structure to initialize.
    - unsigned int tile_count: Total number of tiles in the tower.

Limitations:
    - Assumes tiles and grid layout are predefined.
    - Positions of tiles are set to default and need further adjustment based on gameplay.
*/
void initialize_tower(Tower *new_tower, unsigned int tile_count)
{
    unsigned int i, row, col;
    new_tower->max_row = 0;
    new_tower->tile_count = tile_count;

    while (i < tile_count)
    {
        initialize_tile(new_tower, &new_tower->tiles[i], 0, 0);
        i++;
    }

    for (row = 0; row < GRID_HEIGHT; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            new_tower->grid[row][col] = GRID_LAYOUT[row][col];
        }
    }
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
void initialize_counter(Counter *new_counter, unsigned int x, unsigned int y, int tile_count)
{
    new_counter->x = x;
    new_counter->y = y;
    new_counter->tile_count = tile_count;
}

/*
----- FUNCTION: move_active_piece_left -----
Purpose:
    - Moves the active player-controlled tetromino to the left by updating its x-coordinate.

Details:
    - This function decreases the x-coordinate of the active tetromino by its velocity in the x-direction.
    - The amount by which the tetromino moves is determined by the value of `velocity_x`, which can be adjusted for different movement speeds.

Parameters:
    - Tetromino *active_piece: Pointer to the active tetromino structure, which contains the x-coordinate and velocity.

Limitations:
    - Assumes that the `velocity_x` value has been properly initialized for the active tetromino.
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
    - The amount by which the tetromino moves is determined by the value of `velocity_x`, which can be adjusted for different movement speeds.

Parameters:
    - Tetromino *active_piece: Pointer to the active tetromino structure, which contains the x-coordinate and velocity.

Limitations:
    - Assumes that the `velocity_x` value has been properly initialized for the active tetromino.
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
    - The amount by which the tetromino moves downward is determined by the value of `velocity_y`, which can be adjusted for different movement speeds.

Parameters:
    - Tetromino *active_piece: Pointer to the active tetromino structure, which contains the y-coordinate and velocity.

Limitations:
    - Assumes that the `velocity_y` value has been properly initialized for the active tetromino.
    - Does not check for boundary conditions or collisions with the bottom of the playing field or other pieces; those must be handled separately.
*/
void drop_active_piece(Tetromino *active_piece)
{
    active_piece->y += active_piece->velocity_y;
}

/*
----- FUNCTION: update_tiles -----
Purpose: Updates the position of tiles in the tower, shifting them down if rows are cleared.

Parameters:
    - Tower *tower: Pointer to the tower structure to update.

Limitations:
    - Assumes that tiles need to be shifted one row down.
    - Does not account for edge cases like tiles already at the bottom row.
*/
void update_tiles(Tower *tower)
{
    int row, col;
    int tile_index = 0;

    for (row = 0; row < GRID_HEIGHT; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            if (tower->grid[row][col] == 1)
            {
                if (tile_index < MAX_TILES_IN_TOWER)
                {
                    tower->tiles[tile_index].x = 225 + (col * 15);
                    tower->tiles[tile_index].y = 41 + (row * 15);

                    tower->tiles[tile_index].width = TILE_WIDTH;
                    tower->tiles[tile_index].height = TILE_HEIGHT;

                    tile_index++;
                }
            }
        }
    }

    tower->tile_count = tile_index;
}

/*
----- FUNCTION: remove_tile_from_array -----
Purpose: Removes a tile from the array of tiles in the tower and shifts subsequent tiles up to fill the gap.

Parameters:
    - Tower *tower: Pointer to the tower structure.
    - unsigned int index: Index of the tile to remove in the array.
*/
void remove_tile_from_array(Tower *tower, unsigned int index)
{
    unsigned int i;
    for (i = index; i < tower->tile_count - 1; i++)
    {
        tower->tiles[i] = tower->tiles[i + 1];
    }

    tower->tile_count--;
}

/*
----- FUNCTION: update_grid -----
Purpose: Updates the grid layout of the tower by shifting rows downward.

Parameters:
    - Tower *tower: Pointer to the tower structure to update.
*/
void update_grid(Tower *tower)
{
    int row;
    for (row = tower->max_row; row >= 0; row--)
    {
        if (is_row_non_empty(tower, row))
        {
            shift_row_down(tower, row);
        }
    }
}

/*
----- FUNCTION: shift_row_down -----
Purpose:
    - Shifts a specified row downwards and updates the positions of tiles accordingly.

Details:
    - This function moves all occupied cells in a specified row to the nearest available position below.
    - It updates the grid and recalculates the y-coordinates of the affected tiles.

Parameters:
    - Tower *tower: Pointer to the tower structure.
    - int row: The row to be shifted down.

Limitations:
    - Assumes the tower grid and tiles are properly initialized.
    - Behavior undefined if row exceeds the grid boundaries.
*/
void shift_row_down(Tower *tower, int row)
{
    int col, target_row;
    unsigned int tile_index;

    for (col = 0; col < GRID_WIDTH; col++)
    {
        if (tower->grid[row][col] != 0)
        {
            target_row = row;
            while (target_row + 1 < GRID_HEIGHT && tower->grid[target_row + 1][col] == 0)
            {
                target_row++;
            }

            if (target_row != row)
            {
                tower->grid[target_row][col] = tower->grid[row][col];
                tower->grid[row][col] = 0;
            }
        }
    }

    for (tile_index = 0; tile_index < tower->tile_count; tile_index++)
    {
        if (tower->tiles[tile_index].y == row * CONST_VELOCITY)
        {
            tower->tiles[tile_index].y = (row + 1) * CONST_VELOCITY;
        }
    }
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
void update_tower(Tetromino *active_piece, Tower *tower)
{
    const int(*layout)[PIECE_SIZE] = NULL;
    layout = cycle_piece_layout(active_piece->curr_index);
    update_piece_layout(active_piece, tower, layout);
    update_grid(tower);
    active_piece->merged = FALSE;
}

/*
----- FUNCTION: update_piece_layout -----
Purpose:
    - Updates the tower by incorporating the active piece's layout and adjusting grid and tile details.

Details:
    - Iterates through the active piece's layout and updates the grid and tiles in the tower.
    - Adjusts the max_row of the tower as needed.

Parameters:
    - Tetromino *active_piece: Pointer to the currently active piece.
    - Tower *tower: Pointer to the tower structure.
    - const int layout[PIECE_SIZE][PIECE_SIZE]: 2D array representing the piece's layout.

Limitations:
    - Assumes the layout dimensions match PIECE_SIZE.
    - May overwrite existing grid data if collision checks are not performed.
*/
void update_piece_layout(Tetromino *active_piece, Tower *tower, const int layout[PIECE_SIZE][PIECE_SIZE])
{
    unsigned int i, j, tile_index;
    unsigned int grid_x, grid_y;

    for (i = 0; i < PIECE_SIZE; i++)
    {
        for (j = 0; j < PIECE_SIZE; j++)
        {
            if (layout[i][j] == 1)
            {
                tile_index = tower->tile_count;
                tower->tiles[tile_index].x = active_piece->x + (j * active_piece->velocity_x);
                tower->tiles[tile_index].y = active_piece->y + (i * active_piece->velocity_y);
                tower->tiles[tile_index].width = TILE_WIDTH;
                tower->tiles[tile_index].height = TILE_HEIGHT;
                tower->tile_count++;

                get_grid_coordinates(active_piece->x + j * active_piece->velocity_x,
                                     active_piece->y + i * active_piece->velocity_y,
                                     &grid_x, &grid_y);

                if (grid_x < GRID_WIDTH && grid_y < GRID_HEIGHT)
                {
                    tower->grid[grid_y][grid_x] = 1;
                    tower->max_row = grid_y;
                }
            }
        }
    }
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
    if (active_piece->x < playing_field->x ||
        active_piece->x + active_piece->width > playing_field->x + playing_field->width)
    {
        return TRUE;
    }

    if (active_piece->y < playing_field->y ||
        active_piece->y + active_piece->height > playing_field->y + playing_field->height)
    {
        return TRUE;
    }

    return FALSE;
}

/*
----- FUNCTION: tile_collision -----
Purpose:
    - Checks if the active piece has collided with a specific tile.

Details:
    - Compares the active piece's layout with the tile's boundaries.
    - Assumes tiles have a slightly smaller collision box to handle overlaps.

Parameters:
    - Tetromino *active_piece: Pointer to the active piece.
    - Tile *tile: Pointer to the tile being checked.

Return:
    - bool: TRUE if a collision occurs, FALSE otherwise.

Limitations:
    - Assumes a fixed offset for collision size.
    - Only supports rectangular tile collision checks.
*/
bool tile_collision(Tetromino *active_piece, Tile *tile)
{
    unsigned int x, y, piece_x, piece_y;
    for (y = 0; y < PIECE_SIZE; y++)
    {
        for (x = 0; x < PIECE_SIZE; x++)
        {
            if (active_piece->layout[y][x] == 1)
            {
                int piece_x = active_piece->x + x * active_piece->velocity_x;
                int piece_y = active_piece->y + y * active_piece->velocity_y;

                if (piece_x + active_piece->velocity_x > tile->x &&
                    piece_x < tile->x + tile->width - OFFSET &&
                    piece_y + active_piece->velocity_y > tile->y &&
                    piece_y < tile->y + tile->height - OFFSET)
                {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

/*
----- FUNCTION: tower_collision -----
Purpose:
    - Checks if the active piece has collided with any tiles in the tower.

Details:
    - Iterates through all tiles in the tower and calls tile_collision for each tile.
    - Returns immediately if a collision is detected.

Parameters:
    - Tetromino *active_piece: Pointer to the active piece.
    - Tower *tower: Pointer to the tower structure.

Return:
    - bool: TRUE if a collision occurs, FALSE otherwise.

Limitations:
    - May become inefficient with a high number of tiles.
    - Assumes the tower's tiles are correctly positioned.
*/
bool tower_collision(Tetromino *active_piece, Tower *tower)
{
    unsigned int i;
    for (i = 0; i < tower->tile_count; i++)
    {
        Tile *current_tile = &tower->tiles[i];
        if (tile_collision(active_piece, current_tile))
        {
            return TRUE;
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
----- FUNCTION: check_row_clearance -----
Purpose:
    - Checks if a row (or rows) in the tower is fully filled.

Details:
    - Iterates through rows near the max_row of the tower.
    - Verifies if all columns in a row are filled.

Parameters:
    - Tower *tower: Pointer to the tower structure.
    - Tetromino *active_piece: Pointer to the active piece.

Return:
    - bool: TRUE if a row is completely filled, FALSE otherwise.

Limitations:
    - Assumes rows are filled sequentially from the bottom up.
    - Dependent on the active piece's dimensions for clearance checks.
*/
bool check_row_clearance(Tower *tower, Tetromino *active_piece)
{
    int row, col;
    unsigned int tile_height;

    tile_height = active_piece->height / 15;

    for (row = tower->max_row; row > tower->max_row - tile_height; row--)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            if (tower->grid[row][col] == 0)
            {
                break;
            }
        }
        if (col == GRID_WIDTH)
        {
            tower->max_row = row;
            return TRUE;
        }
    }
    return FALSE;
}

/*
----- FUNCTION: is_row_non_empty -----
Purpose:
    - Checks if a specific row contains at least one occupied cell.

Details:
    - Iterates through all columns of a given row and returns TRUE if any column is occupied.

Parameters:
    - Tower *tower: Pointer to the tower structure.
    - int row: The row to check.

Return:
    - bool: TRUE if the row is non-empty, FALSE otherwise.

Limitations:
    - Does not differentiate between partially and fully filled rows.
    - Assumes valid row indices within the grid boundaries.
*/
bool is_row_non_empty(Tower *tower, int row)
{
    int col;
    for (col = 0; col < GRID_WIDTH; col++)
    {
        if (tower->grid[row][col] != 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}
