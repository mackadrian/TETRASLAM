#ifndef MODEL_H
#define MODEL_H

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define MAX_TILES_PER_TETROMINO 4
#define MAX_TILES_PER_ROW 10
#define MAX_PLAYER_TETROMINOES 7
#define MAX_TILES_IN_TOWER 100
#define MAX_PER_COLUMN 100

typedef unsigned int bool;
#define TRUE 1
#define FALSE 0

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
  bool collision;
} Field;

typedef struct
{
  unsigned int x, y;
  unsigned int width, height;
  Tile tiles[MAX_TILES_IN_TOWER];
  unsigned int tile_count;
  bool collision;
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

void initialize_tile(Tile *new_tile, unsigned int x, unsigned int y);
void initialize_tetromino(Tetromino *new_tetromino, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
void initialize_field(Field *new_field, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
void initialize_tower(Tower *new_tower, unsigned int x, unsigned int y,
                      unsigned int width, unsigned int height, unsigned int tile_count);
void initialize_counter(Counter *new_counter, unsigned int x, unsigned int y, int tile_count);
bool tile_collision(Tile *tile1, Tile *tile2);

#endif
