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

Parameters: const Model model	model address
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
void render_active_piece(const Model *model, UINT16 *base_16)
{
    plot_bitmap_16(base_16, model->active_piece.x, model->active_piece.y, I_piece, 61, 1);
}

/*
----- FUNCTION: render_playing_field -----
Purpose: renders the playing field boundaries

Parameters: const Model model	model address
            UINT16 base_16      short size FB pointer
*/
void render_playing_field(const Model *model, UINT16 *base_16)
{
    plot_bitmap_16(base_16, model->playing_field.x, model->playing_field.y, playing_field, 303, 10);
}

/*
----- FUNCTION: render_all_tiles -----
Purpose: renders all the initialized tiles into the playing field

Parameters: const Model model	model address
            UINT16 base_16      short size FB pointer
Assumptions: - Must understand the coordinates for plotting within the playing field.
             - Tiles must be initialized a proper coordinate otherwise tile is rendered at (0,0).
*/
void render_all_tiles(const Model *model, UINT16 *base_16)
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

Parameters: const Model model	model address
            UINT16 base_16      short size FB pointer
Assumptions: - Must know the tiles needed to be plot.
             - Initializing counter is independent from the tiles.
*/
void render_counter(const Model *model, UINT8 *base_8)
{
    char buffer[10];
    sprintf(buffer, "%d %d %d",
            (model->counter.tile_count / 100) % 10,
            (model->counter.tile_count / 10) % 10,
            model->counter.tile_count % 10);
    plot_text(base_8, model->counter.x, model->counter.y, font, "-+- C O U N T E R -+-");
    plot_text(base_8, model->counter.x, model->counter.y + COUNTER_Y_OFFSET, font, "     ");
    plot_text(base_8, model->counter.x + COUNTER_DIGIT_OFFSET, model->counter.y + COUNTER_Y_OFFSET, font, buffer);
    plot_text(base_8, model->counter.x + COUNTER_MAX_OFFSET, model->counter.y + COUNTER_Y_OFFSET, font, "  /  2 0 0    ");
}