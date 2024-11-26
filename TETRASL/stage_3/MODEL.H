#ifndef MODEL_H
#define MODEL_H

#include "LAYOUT.H"
#include "TYPES.H"

#define TILE_WIDTH 14
#define TILE_HEIGHT 14
#define CONST_VELOCITY 16
#define MAX_TILES_PER_TETROMINO 4
#define MAX_TILES_PER_ROW 10
#define MAX_PLAYER_TETROMINOES 7
#define MAX_TILES_IN_TOWER 200
#define MAX_PER_COLUMN 100

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
  unsigned int width, height;
  unsigned int tile_count, curr_index;
  int velocity_x, velocity_y;
  bool merged, dropped;
  const int (*layout)[PIECE_SIZE];
} Tetromino;

typedef struct
{
  unsigned int x, y;
  unsigned int width, height;
} Field;

typedef struct
{
  unsigned int max_row;
  unsigned int tile_count;
  unsigned int is_row_full;
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

/*Helper Functions*/
void get_grid_coordinates(Field *playing_field,
                          unsigned int x, unsigned int y,
                          unsigned int *grid_x, unsigned int *grid_y);
const int (*cycle_piece_layout(int curr_index))[PIECE_SIZE];

/*Initializers*/
void initialize_grid(Tower *new_tower, int layout[GRID_HEIGHT][GRID_WIDTH]);
void initialize_tower(Tower *new_tower, int layout[GRID_HEIGHT][GRID_WIDTH]);
void initialize_layout(Tetromino *new_tetromino, TetrominoType type);
void initialize_tetromino(Tetromino *new_tetromino, unsigned int x, unsigned int y, unsigned int width, unsigned int height, TetrominoType type);
void initialize_field(Field *new_field, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
void initialize_counter(Counter *new_counter, Tower *tower, unsigned int x, unsigned int y);

/*Behaviours*/
void move_active_piece_left(Tetromino *active_piece);
void move_active_piece_right(Tetromino *active_piece);
void drop_active_piece(Tetromino *active_piece);
void update_tower(Field *playing_field, Tetromino *active_piece, Tower *tower);
void update_counter(Counter *counter, Tower *tower);

/*Collisions*/
void check_row(Tower *tower, Tetromino *active_piece);
bool player_bounds_collision(Tetromino *active_piece, Field *playing_field);
bool tower_collision(Tetromino *active_piece, Tower *tower, Field *playing_field);
bool fatal_tower_collision(Tower *tower);
bool win_condition(Tower *tower);

#endif
