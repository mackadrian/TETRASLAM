#include "model.h"

/*
bool check_collision(Tetromino *piece, Tower *tower, Field *field, int new_x, int new_y)
{
  bool collided = false;

  if (new_x < 0 || new_x + piece->width > FIELD_WIDTH)
  {
    collided = true;
  }
  if (new_y + piece->height > FIELD_HEIGHT)
  {
    collided = true;
  }


  for (int i = 0; i < piece->height; ++i) {
    for (int j = 0; j < piece->width; ++j) {
      if (tower->grid[new_y + i][new_x + j] == 1) {
        return true;
      }
    }
  }

  return collided;
}

void move_piece(Tetromino *piece, Tower *tower, Field *field, Direction dir)
{
    int new_x = piece->x;
    int new_y = piece->y;

    switch (dir) {
        case LEFT:
            new_x -= 1;
            break;
        case RIGHT:
            new_x += 1;
            break;
        case DROP:
            new_y += 1;
            break;
        default:
            return;
    }

    if (!check_collision(piece, tower, field, new_x, new_y)) {
        piece->x = new_x;
        piece->y = new_y;
    } else if (dir == DROP) {
        piece->merge = true;
        merge_with_tower(piece, tower);
    }
}
*/



