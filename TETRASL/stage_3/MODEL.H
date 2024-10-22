#ifndef MODEL_H
#define MODEL_H

#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define MAX_TILES_PER_TETROMINO 4
#define MAX_TILES_PER_ROW 10
#define MAX_PLAYER_TETROMINOES 7
#define MAX_TILES_IN_TOWER 100
#define MAX_PER_COLUMN 100

typedef enum
{
  LEFT,
  RIGHT
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
  int merged, dropped;
} Tetromino;

typedef struct
{
  unsigned int x, y;
  unsigned int width, height;
  unsigned int tile_count;
  int collided;
} Field;

typedef struct
{
  unsigned int x, y;
  unsigned int width, height;
  Tile tile[MAX_TILES_IN_TOWER];
  unsigned int tile_count;
  int collided;
} Tower;

typedef struct
{
  unsigned int x, y;
  int tile_count;
} Counter;

typedef struct
{
  Tetromino active_piece;
  Tetromino player_pieces[MAX_PLAYER_TETROMINOES];
  Field playing_field;
  Tower tower;
  Counter counter;
} Model;

void move_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower, Direction direction);
void drop_active_piece(Tetromino *active_piece, Field *playing_field, Tower *tower);
void reset_active_pos(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower);
void cycle_active_piece(Tetromino *active_piece, Tetromino pieces[], Field *playing_field, Tower *tower);
void merge_active_piece_to_tower(Tetromino *active_piece, Tower *tower);
int check_tower_collision(Tetromino *active_piece, Tower *tower);

#endif
