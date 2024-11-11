#ifndef MODEL_H
#define MODEL_H

#include "LAYOUT.H"

#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define MAX_TILES_PER_TETROMINO 4
#define MAX_TILES_PER_ROW 10
#define MAX_PLAYER_TETROMINOES 7
#define MAX_TILES_IN_TOWER 100
#define MAX_PER_COLUMN 100

#define TRUE 1
#define FALSE 0
typedef unsigned int bool;

typedef enum
{
  LEFT,
  RIGHT,
  DROP
} Direction;

typedef enum
{
  I_PIECE,
  J_PIECE,
  L_PIECE,
  O_PIECE,
  S_PIECE,
  T_PIECE,
  Z_PIECE
} TetrominoType;

typedef struct
{
  unsigned int x, y;
  unsigned width, height;
} Tile;

typedef struct
{
  unsigned int x, y;
  unsigned int width, height;
  unsigned int tile_count, curr_index;
  int velocity_x, velocity_y;
  bool merged, dropped;
  int layout[PIECE_SIZE][PIECE_SIZE];
} Tetromino;

typedef struct
{
  unsigned int x, y;
  unsigned int width, height;

} Field;

typedef struct
{
  Tile tiles[MAX_TILES_IN_TOWER];
  unsigned int max_row;
  unsigned int tile_count;
  int grid[GRID_HEIGHT][GRID_WIDTH];
} Tower;

typedef struct
{
  unsigned int x, y;
  unsigned int tile_count;
} Counter;

typedef struct
{
  Tetromino active_piece;
  Tetromino player_pieces[MAX_PLAYER_TETROMINOES];
  Field playing_field;
  Tower tower;
  Counter counter;
} Model;

/*Initializers*/
void initialize_tile(Tower *tower, Tile *new_tile, unsigned int x, unsigned int y);
void initialize_layout(Tetromino *new_tetromino, TetrominoType type);
void initialize_tetromino(Tetromino *new_tetromino, unsigned int x, unsigned int y, unsigned int width, unsigned int height, TetrominoType type);
void initialize_field(Field *new_field, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
void initialize_tower(Tower *new_tower, unsigned int tile_count);
void initialize_counter(Counter *new_counter, unsigned int x, unsigned int y, int tile_count);

/*Helper Functions*/
void get_grid_coordinates(unsigned int x, unsigned int y,
                          unsigned int *grid_x, unsigned int *grid_y);
const int (*cycle_piece_layout(int curr_index))[PIECE_SIZE];

/*Behaviours*/
void update_counter(Counter *counter, Tower *tower);
void update_active_piece(Tetromino *active_piece, Direction direction);
void update_tower(Tetromino *active_piece, Tower *tower);
void update_tiles(Tower *tower, unsigned int cleared_row);
void update_piece_layout(Tetromino *active_piece, Tower *tower, const int layout[PIECE_SIZE][PIECE_SIZE]);

/*Collisions*/
bool player_bounds_collision(Tetromino *active_piece, Field *playing_field);
bool tile_collision(Tetromino *active_piece, Tile *tile);
bool tower_collision(Tetromino *active_piece, Tower *tower);
bool fatal_tower_collision(Tower *tower, Field *playing_field);

#endif
