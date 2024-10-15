#include "model.h"
#include <osbind.h>
#include <stdio.h>

/* FUNCTION DECLARATIONS*/
void print_model(Model *model);

/* SNAPSHOT*/
Model testSnapshot = 
{
    /* 7 tetrominoes for player*/
    {
        {171 + (16 * 4), 41, 16, 61, 4, 0, 0, -1, -1}, 
        {171 + (16 * 4), 41, 31, 46, 4, 0, 0, -1, -1}, 
        {171 + (16 * 4), 41, 31, 46, 4, 0, 0, -1, -1},
        {171 + (16 * 4), 41, 31, 31, 4, 0, 0, -1, -1},
        {171 + (16 * 4), 41, 46, 31, 4, 0, 0, -1, -1},
        {171 + (16 * 4), 41, 46, 31, 4, 0, 0, -1, -1},
        {171 + (16 * 4), 41, 46, 31, 4, 0, 0, -1, -1}
    },
    /* playing field*/
    {224, 40, 153, 303, 100, -1, -1, -1},
    /*tower*/
    {225, 41, 100, 0, 0, -1, -1, -1},
    /*tile counter*/
    {329 + (48 * 2), 40, 100}
};


int main ()
{
    /* Set screen to white */
    Cnecin();
    printf("\033E\033f\n");
    print_model(&testSnapshot);

    Cnecin();
    printf("\033E\033f\n");
    
     return 0;
}

void print_model(Model *model)
{
    int i;
    printf("Player Tetrominoes:\n");
    for (i = 0; i < 7; i++) {
        Tetromino *tetromino = &model->player_pieces[i];
        printf("  Tetromino %d: x=%u, y=%u, width=%u, height=%u, tile_count=%u, delta_x=%d, delta_y=%d, merged=%d, dropped=%d\n",
            i,
            tetromino->x,
            tetromino->y,
            tetromino->width,
            tetromino->height,
            tetromino->tile_count,
            tetromino->delta_x,
            tetromino->delta_y,
            tetromino->merged,
            tetromino->dropped);
    }
    printf("Playing Field:\n");
    printf("  x=%u, y=%u, width=%u, height=%u, tile_count=%u, merged=%d, row_cleared=%d, collided=%d\n",
           model->playing_field.x, 
           model->playing_field.y, 
           model->playing_field.width,
           model->playing_field.height,
           model->playing_field.tile_count, 
           model->playing_field.merged, 
           model->playing_field.row_cleared, 
           model->playing_field.collided);
    
    printf("Tower:\n");
    printf("  x=%u, y=%u, tile_count=%u, delta_x=%d, delta_y=%d, merged=%d, row_cleared=%d, collided=%d\n",
           model->tower.x, 
           model->tower.y, 
           model->tower.tile_count, 
           model->tower.delta_x, 
           model->tower.delta_y, 
           model->tower.merged, 
           model->tower.row_cleared, 
           model->tower.collided);
    
    printf("Tile Counter:\n");
    printf("  x=%u, y=%u, tile_count=%u\n",
           model->counter.x, 
           model->counter.y, 
           model->counter.tile_count);
}
