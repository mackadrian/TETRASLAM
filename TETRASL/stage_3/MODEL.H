#ifndef MODEL_H
#define MODEL_H


#define FIELD_WIDTH 153 
#define FIELD_HEIGHT 303

typedef struct
{
  unsigned int x, y;
  unsigned int width, height;
  unsigned int tile_count;
  int delta_x, delta_y;
  int merged, dropped;
} Tetromino;

typedef struct 
{
  unsigned int x, y;
  unsigned int width, height;
  unsigned int tile_count;
  int merged, row_cleared, collided;
} Field;

typedef struct 
{
  unsigned int x, y;
  unsigned int tile_count;
  int delta_x, delta_y;
  int merged, row_cleared, collided;
} Tower;

typedef struct 
{
  unsigned int x, y;
  unsigned int tile_count;
}Tile;

typedef struct
{
  Tetromino player_pieces[7];
  Field playing_field;
  Tower tower;
  Tile counter;
} Model;

/*
bool check_collision(Tetromino *piece, Tower *tower,
                       Field *field, int new_x, int new_y);
void move_piece(Player *piece, Tower *tower,
                 Field *field, Direction dir);
*/


#endif
