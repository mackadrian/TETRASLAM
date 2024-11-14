/**
 * @file RENDER.C
 * @brief contains all of the render functions
 * @author Mack Bautista
 */
#include "render.h"
#include <stdio.h>

#define COUNTER_Y_OFFSET 15
#define COUNTER_DIGIT_OFFSET 21
#define COUNTER_MAX_OFFSET 61

/*
----- FUNCTION: render -----
Purpose: master render of the TETRASLAM

Parameters: Model model	model address
            UINT16 base_16      short size FB pointer
            UINT32 base_32      longword size FB pointer
            UINT8 base_8        char size FB pointer
*/
void render(const Model *model, UINT32 *base_32, UINT16 *base_16, UINT8 *base_8)
{
    render_active_piece(model, base_16);
    render_playing_field(model, base_16);
    render_all_tiles(model, base_16);
    render_counter(model, base_8);
}

/*
----- FUNCTION: render_active_piece -----
Purpose: renders the playable active piece into the screen

Parameters: const Model model	model address
            UINT16 base_16      short size FB pointer
*/
void render_active_piece(Model *model, UINT16 *base_16)
{
    const UINT16 *curr_piece;
    switch (model->active_piece.curr_index)
    {
    case 0:
        curr_piece = I_piece;
        break;
    case 1:
        curr_piece = J_piece;
        break;
    case 2:
        curr_piece = L_piece;
        break;
    case 3:
        curr_piece = O_piece;
        break;
    case 4:
        curr_piece = S_piece;
        break;
    case 5:
        curr_piece = T_piece;
        break;
    case 6:
        curr_piece = Z_piece;
        break;
    default:
        break;
    }
    plot_bitmap_16(base_16, model->active_piece.x, model->active_piece.y,
                   curr_piece, model->active_piece.height, model->active_piece.width / 15);
}

/*
----- FUNCTION: render_playing_field -----
Purpose: renders the playing field boundaries

Parameters: const Model model	model address
            UINT16 base_16      short size FB pointer
*/
void render_playing_field(Model *model, UINT16 *base_16)
{
    plot_bitmap_16(base_16, model->playing_field.x, model->playing_field.y,
                   playing_field, model->playing_field.height, model->playing_field.width / 15);
}

/*
----- FUNCTION: render_all_tiles -----
Purpose: renders all the initialized tiles into the playing field

Parameters: const Model model	model address
            UINT16 base_16      short size FB pointer
Assumptions: - Must understand the coordinates for plotting within the playing field.
             - Tiles must be initialized a proper coordinate otherwise tile is rendered at (0,0).
*/
void render_all_tiles(Model *model, UINT16 *base_16)
{
    unsigned int i = 0;
    while (i < model->tower.tile_count)
    {
        plot_bitmap_16(base_16, model->tower.tiles[i].x, model->tower.tiles[i].y, tile, 16, 1);
        i++;
    }
}

/*
----- FUNCTION: render_counter -----
Purpose: renders the tile counter outside of the playing field

Parameters:
    const Model *model  model address containing game data
    UINT8 *base_8       short size frame buffer pointer
Assumptions:
    - The tiles needed to be plotted must be known.
    - Initializing the counter is independent of the tiles.
*/
void render_counter(Model *model, UINT8 *base_8)
{
    char buffer[10];

    buffer[0] = '0' + (model->counter.tile_count / 100) % 10;
    buffer[1] = ' ';
    buffer[2] = '0' + (model->counter.tile_count / 10) % 10;
    buffer[3] = ' ';
    buffer[4] = '0' + model->counter.tile_count % 10;
    buffer[5] = '\0';

    plot_text(base_8, model->counter.x, model->counter.y, font, "-+- C O U N T E R -+-");
    plot_text(base_8, model->counter.x, model->counter.y + COUNTER_Y_OFFSET, font, "     ");
    plot_text(base_8, model->counter.x + COUNTER_DIGIT_OFFSET, model->counter.y + COUNTER_Y_OFFSET, font, buffer);
    plot_text(base_8, model->counter.x + COUNTER_MAX_OFFSET, model->counter.y + COUNTER_Y_OFFSET, font, "  /  2 0 0    ");
}