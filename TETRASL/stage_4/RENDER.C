/**
 * @file RENDER.C
 * @brief contains all of the render functions
 * @author Mack Bautista
 */
#include "render.h"
#include <stdio.h>

/*
----- FUNCTION: render -----
Purpose: master render of the TETRASLAM

Parameters: const Model model	model address
            UINT16 base_16      short size FB pointer
            UINT32 base_32      longword size FB pointer
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
*/
void render_active_piece(const Model *model, UINT16 *base_16)
{
    plot_bitmap_16(base_16, model->active_piece.x, model->active_piece.y, I_piece, 61, 1);
}

/*
----- FUNCTION: render_playing_field -----
*/
void render_playing_field(const Model *model, UINT16 *base_16)
{
    plot_bitmap_16(base_16, model->playing_field.x, model->playing_field.y, playing_field, 303, 10);
}

/*
----- FUNCTION: render_all_tiles -----
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

void render_counter(const Model *model, UINT8 *base_8)
{
    char buffer[10];
    sprintf(buffer, "%3d", model->counter.tile_count);
    plot_text(base_8, model->counter.x, model->counter.y, font, "-+-+- C O U N T E R -+-+-");
    plot_text(base_8, model->counter.x, model->counter.y + 15, font, "     ");
    plot_text(base_8, model->counter.x + 20, model->counter.y + 15, font, buffer);
    plot_text(base_8, model->counter.x + 50, model->counter.y + 15, font, "  /  1 0 0     ");
}