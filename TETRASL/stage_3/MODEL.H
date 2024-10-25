#ifndef MODEL_H
#define MODEL_H

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
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
} Tetromino;

typedef struct
{
  unsigned int x, y;
  unsigned int width, height;
} Field;

typedef struct
{
  Tile tiles[MAX_TILES_IN_TOWER];
  unsigned int tiles_per_row[MAX_TILES_PER_ROW];
  unsigned int tile_count;
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
void initialize_tile(Tile *new_tile, unsigned int x, unsigned int y);
void initialize_tetromino(Tetromino *new_tetromino, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
void initialize_field(Field *new_field, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
void initialize_tower(Tower *new_tower, unsigned int tile_count);
void initialize_counter(Counter *new_counter, unsigned int x, unsigned int y, int tile_count);

/*Behaviours*/
void update_counter(Counter *counter, Tower *tower);
void update_active_piece(Tetromino *active_piece, Direction direction);
void update_tower(Tower *tower, Tetromino *active_piece);

/*Collisions*/
bool out_of_bounds_collision(Tetromino *active_piece, Field *playing_field);
bool tile_collision(Tetromino *active_piece, Tile *tile);
bool tower_collision(Tetromino *active_piece, Tower *tower);

#endif
