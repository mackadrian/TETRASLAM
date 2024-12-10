#ifndef RENDER_H
#define RENDER_H

#include "raster.h"
#include "model.h"
#include "bitmaps.h"
#include "font.h"
#include "types.h"

void render(const Model *model, UINT32 *base_32, UINT16 *base_16, UINT8 *base_8);
void render_active_piece(Model *model, UINT16 *base_16);
void render_playing_field(Model *model, UINT16 *base_16);
void render_tower(const Model *model, UINT16 *base_16);
void render_counter(Model *model, UINT8 *base_8);
void render_main_menu(UINT16 *base_16);

#endif