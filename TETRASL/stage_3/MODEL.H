#ifndef MODEL_H
#define MODEL_H

typedef struct
{
  unsigned int x, y;
  unsigned int tile_count, cycle_count;
  int delta_x, delta_y;
  bool merge, dropped, cycled;
} Tetromino;

typedef struct
{
  Tetromino pieces[7];
} Player;

typedef struct 
{
  unsigned int x, y;
  unsigned int tile_count;
  int delta_x, delta_y;
  bool merge, row_cleared, collided;
} Tower;

typedef struct 
{
  unsigned x, y;
  unsigned int tile_count;
}Field;


typedef struct 
{
  unsigned int x, y;
  unsigned int tile_count;
}Tile;

typedef struct
{
  Player player_piece;
  Tower tower;
  Field playing_field;
  Tile counter; 
} Model;

void move_piece(Player *piece);


#endif
