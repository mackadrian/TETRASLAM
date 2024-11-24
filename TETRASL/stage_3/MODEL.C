/**
 * @file MODEL.C
 * @brief contains all of TETRASLAM's object behaviour functions.
 * @author Mack Bautista
 */

#include "model.h"
#include "layout.h"
#include <stdio.h>

#define CONST_VELOCITY 16

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
void initialize_tile(Field *playing_field, Tower *tower, Tile *new_tile,
                     unsigned int x, unsigned int y)
{
    unsigned int grid_x, grid_y;

    new_tile->x = x;
    new_tile->y = y;
    new_tile->width = TILE_WIDTH;
    new_tile->height = TILE_HEIGHT;

    get_grid_coordinates(playing_field, x, y, &grid_x, &grid_y);

    if (grid_x < GRID_WIDTH && grid_y < GRID_HEIGHT)
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
----- FUNCTION: initialize_tower -----
Purpose: Initializes the tower structure, setting its tiles and grid layout.

Parameters:
    - Tower *new_tower: Pointer to the tower structure to initialize.
    - unsigned int tile_count: Total number of tiles in the tower.

Limitations:
    - Assumes tiles and grid layout are predefined.
    - Positions of tiles are set to default and need further adjustment based on gameplay.
*/
void initialize_tower(Field *playing_field, Tower *new_tower, unsigned int tile_count)
{
    unsigned int i, row, col;
    new_tower->max_row = 0;
    new_tower->tile_count = tile_count;

    while (i < tile_count)
    {
        initialize_tile(playing_field, new_tower, &new_tower->tiles[i], 0, 0);
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
void initialize_counter(Counter *new_counter, Tower *tower, unsigned int x, unsigned int y)
{
    new_counter->x = x;
    new_counter->y = y;
    new_counter->tile_count = tower->tile_count;
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
    const int(*layout)[PIECE_SIZE] = cycle_piece_layout(active_piece->curr_index);
    update_piece_layout(playing_field, active_piece, tower, layout);
    active_piece->merged = FALSE;
}

/*
----- FUNCTION: update_counter -----
Purpose:
    - Updates the counter to reflect the current tile count from the tower.

Details:
    - Sets the `tile_count` of the `counter` to match the `tile_count` of the `tower`.
    - This ensures the counter displays the correct number of tiles in the tower at any given moment.

Parameters:
    - Counter *counter: Pointer to the counter structure that tracks the tile count.
    - Tower *tower: Pointer to the tower structure containing the current tile count.

Limitations:
    - Assumes the `counter` and `tower` structures are initialized and valid.
    - Only updates the `tile_count` field of the `counter`; no other tower-related state is modified.
*/
void update_counter(Counter *counter, Tower *tower)
{
    counter->tile_count = tower->tile_count;
}

/*
----- FUNCTION: update_piece_layout -----
Purpose:
    - Updates the layout of the active piece, placing its tiles in the tower and marking their positions in the grid.

Details:
    - Uses the active piece's layout matrix to determine the positions of its tiles.
    - Calls `initialize_tile` to set up each tile and update the tower's grid.

Parameters:
    - Field *playing_field: Pointer to the playing field structure.
    - Tetromino *active_piece: Pointer to the active tetromino.
    - Tower *tower: Pointer to the tower structure.
    - const int layout[PIECE_SIZE][PIECE_SIZE]: 2D array representing the layout of the active piece.

Limitations:
    - Assumes `playing_field`, `active_piece`, and `tower` are initialized and valid.
*/
void update_piece_layout(Field *playing_field, Tetromino *active_piece, Tower *tower, const int layout[PIECE_SIZE][PIECE_SIZE])
{
    unsigned int i, j;
    unsigned int tile_x, tile_y, grid_x, grid_y;

    for (i = 0; i < PIECE_SIZE; i++)
    {
        for (j = 0; j < PIECE_SIZE; j++)
        {
            if (layout[i][j] == 1)
            {
                tile_x = active_piece->x + (j * CONST_VELOCITY);
                tile_y = active_piece->y + (i * CONST_VELOCITY);

                grid_x = (tile_x - playing_field->x) >> PIECE_SIZE;
                grid_y = (tile_y - playing_field->y) >> PIECE_SIZE;

                if (grid_x < GRID_WIDTH && grid_y < GRID_HEIGHT)
                {
                    tower->grid[grid_y][grid_x] = 1;
                }
            }
        }
    }

    update_tiles(playing_field, tower);
}

/*
----- FUNCTION: update_tiles -----
Purpose:
    - Updates the properties of each tile in `tower->tiles` based on the current state of the grid.

Details:
    - Iterates over the `tower->tiles` array and updates the `x` and `y` properties of each tile.
    - The `y` position of each tile is updated based on its new position in the grid.
    - The `x` position of each tile is updated based on its current position in the grid.

Parameters:
    - Tower *tower:    Pointer to the tower structure.
*/
void update_tiles(Field *playing_field, Tower *tower)
{
    unsigned int x, y;
    unsigned int pixel_x, pixel_y;

    tower->tile_count = 0;

    for (y = 0; y < GRID_HEIGHT; y++)
    {
        for (x = 0; x < GRID_WIDTH; x++)
        {
            if (tower->grid[y][x] == 1)
            {
                pixel_x = (x * CONST_VELOCITY) + playing_field->x;
                pixel_y = (y * CONST_VELOCITY) + playing_field->y;
                initialize_tile(playing_field, tower, &tower->tiles[tower->tile_count], pixel_x, pixel_y);

                tower->tile_count++;
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
----- FUNCTION: tile_collision -----
Purpose:
    - Checks if the active piece has collided with a specific tile.
    - Uses the active piece's layout and current position to check for overlap.

Details:
    - Efficiently checks only the filled blocks of the piece's layout.
    - Assumes the piece's velocity has been applied to determine its next position.

Parameters:
    - Tetromino *active_piece: Pointer to the active piece.
    - Tile *tile: Pointer to the tile being checked.

Return:
    - bool: TRUE if a collision occurs, FALSE otherwise.
*/
bool tile_collision(Tetromino *active_piece, Tile *tile)
{
    int x, y, piece_x, piece_y, piece_left, piece_right, piece_top, piece_bottom;
    piece_left = active_piece->x;
    piece_right = active_piece->x + (PIECE_SIZE * active_piece->velocity_x);
    piece_top = active_piece->y;
    piece_bottom = active_piece->y + (PIECE_SIZE * active_piece->velocity_y);

    for (y = 0; y < PIECE_SIZE; y++)
    {
        for (x = 0; x < PIECE_SIZE; x++)
        {
            if (active_piece->layout[y][x] == TRUE)
            {
                piece_x = piece_left + x * active_piece->velocity_x;
                piece_y = piece_top + y * active_piece->velocity_y;

                if (piece_x + PIECE_SIZE > tile->x &&
                    piece_x < tile->x + tile->width &&
                    piece_y + PIECE_SIZE > tile->y &&
                    piece_y < tile->y + tile->height)
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
    - Efficiently checks only the filled blocks of the active piece's layout.
    - Reduces the number of comparisons by checking against only relevant tiles.

Parameters:
    - Tetromino *active_piece: Pointer to the active piece.
    - Tower *tower: Pointer to the tower structure.

Return:
    - bool: TRUE if a collision occurs, FALSE otherwise.
*/
bool tower_collision(Tetromino *active_piece, Tower *tower)
{
    unsigned int i;
    int piece_left = active_piece->x;
    int piece_right = active_piece->x + (PIECE_SIZE * active_piece->velocity_x);
    int piece_top = active_piece->y;
    int piece_bottom = active_piece->y + (PIECE_SIZE * active_piece->velocity_y);

    for (i = 0; i < tower->tile_count; i++)
    {
        Tile *current_tile = &tower->tiles[i];

        if (current_tile->x < piece_right && current_tile->x + current_tile->width > piece_left &&
            current_tile->y < piece_bottom && current_tile->y + current_tile->height > piece_top)
        {
            if (tile_collision(active_piece, current_tile))
            {
                return TRUE;
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
