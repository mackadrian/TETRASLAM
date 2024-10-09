#ifndef RASTER_H
#define RASTER_H

#include "types.h"

/*
----- FUNCTION: clear_screan -----
Author: Marc Schroeder
*/
void clear_screen();

void plot_bitmap_16(UINT16 *base, int x, int y,
                    const UINT16 *bitmap, unsigned int height);

void plot_bitmap_8(UINT8 *base, int x, int y,
                   const UINT8 *bitmap, unsigned char height);

#endif
