/**
 * @file RENDER.C
 * @brief contains all of the render functions
 * @author Mack Bautista
 */
#include "render.h"
#include <stdio.h>

/*
----- FUNCTION: render -----
Purpose:
    - Master render function for the TETRASLAM game.
    - Calls all individual render functions to draw game components.

Parameters:
    - const Model *model:   Model address containing game state and data.
    - UINT32 *base_32:      Longword-sized frame buffer pointer.
    - UINT16 *base_16:      Short-sized frame buffer pointer.
    - UINT8 *base_8:        Byte-sized frame buffer pointer.

Limitations:
    - Frame buffer pointers must point to valid memory regions.
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
Purpose:
    - Renders the currently active piece onto the playing field.

Parameters:
    - const Model *model:   Model address containing the active piece data.
    - UINT16 *base_16:      Short-sized frame buffer pointer.

Limitations:
    - The active piece must be correctly initialized in the model.
    - Assumes the active piece's bitmap is valid for rendering.
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
Purpose:
    - Renders the boundaries of the playing field.

Parameters:
    - const Model *model:   Model address containing playing field data.
    - UINT16 *base_16:      Short-sized frame buffer pointer.

Limitations:
    - The playing field dimensions must align with the frame buffer dimensions.
*/
void render_playing_field(Model *model, UINT16 *base_16)
{
    plot_bitmap_16(base_16, model->playing_field.x, model->playing_field.y,
                   playing_field, model->playing_field.height, model->playing_field.width / 15);
}

/*
----- FUNCTION: render_all_tiles -----
Purpose:
    - Renders all initialized tiles within the playing field.

Parameters:
    - const Model *model:    Model address containing tower tile data.
    - UINT16 *base_16:       Short-sized frame buffer pointer.

Limitations:
    - Assumes valid tile coordinates are provided.
    - Tile count must not exceed the tower's tile array capacity.
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
Purpose:
    - Renders the tile counter outside the playing field.

Parameters:
    - const Model *model:   Model address containing counter data.
    - UINT8 *base_8:        Byte-sized frame buffer pointer.

Limitations:
    - Assumes the font data is initialized and compatible with `plot_text`.
    - The counter's rendering logic is dependent on the tile count being within [0, 200].
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
    plot_text(base_8, model->counter.x, model->counter.y + 15, font, "     ");
    plot_text(base_8, model->counter.x + 21, model->counter.y + 15, font, buffer);
    plot_text(base_8, model->counter.x + 61, model->counter.y + 15, font, "  /  2 0 0    ");
}
