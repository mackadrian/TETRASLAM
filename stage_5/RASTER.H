#ifndef RASTER_H
#define RASTER_H

#include "types.h"

void clear_screen(UINT32 *base);

void plot_bitmap_16(UINT16 *base, int x, int y,
                    const UINT16 *bitmap,
                    unsigned int height, unsigned int width);

void clear_bitmap_16(UINT16 *base, int x, int y,
                     const UINT16 *bitmap,
                     unsigned int height, unsigned int width);

void plot_char(UINT8 *base, int x, int y,
               const UINT8 *font, int ascii);

void plot_text(UINT8 *base, int x, int y,
               const UINT8 *font, const char *text);

#endif
