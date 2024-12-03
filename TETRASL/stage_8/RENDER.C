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
    render_tower(model, base_16);
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
                   curr_piece, model->active_piece.height, model->active_piece.width >> 4);
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
                   playing_field, model->playing_field.height, model->playing_field.width >> 4);
}

/*
----- FUNCTION: render_tower -----
Purpose:
    - Renders all the tiles in the tower by reading the 'model->tower->grid' and rendering the tiles accordingly.

Parameters:
    - const Model *model:    Model address containing tower data (specifically the tower's grid).
    - UINT16 *base_16:       Pointer to the frame buffer where the tiles will be rendered.

Limitations:
    - Assumes the grid and frame buffer are properly initialized and valid.
    - The tower grid dimensions should not exceed the available frame buffer space.
*/
void render_tower(const Model *model, UINT16 *base_16)
{
    int row, col;
    int tile_value;

    for (row = 0; row < GRID_HEIGHT; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            if (model->tower.grid[row][col] == 1)
            {
                plot_bitmap_16(base_16, model->playing_field.x + (col * model->active_piece.velocity_x),
                               model->playing_field.y + (row * model->active_piece.velocity_y), tile, 16, 1);
            }
        }
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
    - Assumes the font data is initialized and compatible with 'plot_text'.
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
    plot_text(base_8, model->counter.x, model->counter.y + 16, font, "     ");
    plot_text(base_8, model->counter.x + 16, model->counter.y + 16, font, buffer);
    plot_text(base_8, model->counter.x + 64, model->counter.y + 16, font, "  /  2 0 0    ");
}

/*
----- FUNCTION: render_counter -----
Purpose:
    - Renders main menu.

Parameters:
    - UINT8 *base_16:        Word-sized frame buffer pointer.
*/
void render_main_menu(UINT16 *base_16)
{
    plot_bitmap_16(base_16, 0, 0, menu, 400, 40);
}
