#include "raster.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTES_PER_SCREEN 256000

/*
----- FUNCTION: clear_screen -----
Purpose: clears all the pixels in the screen

Parameters: UINT16 base 	(unsigned int pointer to frame buffer)

Limitations: Can only pass a bitmap, height, and frame buffer pointer that is
			 strictly for unsigned int size.
			 Must be plotted within the 640 x 400 boundaries otherwise doesn't plot anything.



*/
void clear_screen(UINT16 *base)
{
	UINT32 *temp = (UINT32 *)base;
	UINT32 *end = temp + (BYTES_PER_SCREEN / 32);
	while (temp < end)
	{
		*temp++ = 0x00000000;
	}
}

/*
----- FUNCTION: plot_bitmap_16 -----
Purpose: plots an unsigned int bitmap size onto the screen
		 with a given (x,y) coordinate

Parameters: UINT16 base	(unsigned int pointer to frame buffer)
			int x (horizontal position)
			int y (vertical position)
			const UINT16 bitmap (bitmap array address)
			unsigned int height (height of the bitmap array)
			unsigned int width (width of the bitmap array)

Assumptions: - Can only pass a bitmap, height, and frame buffer pointer that is
			   strictly for unsigned int size.
			 - Must be plotted within the 640 x 400 boundaries otherwise doesn't plot anything.
			 - Weird behaviour occurs when plotting close to the right edge boundary.



*/
void plot_bitmap_16(UINT16 *base, int x, int y,
					const UINT16 *bitmap,
					unsigned int height, unsigned int width)
{
	int i, j;
	UINT16 *loc = base + y * 40 + (x >> 4);

	for (i = 0; i < height; i++)
	{
		UINT16 *row_loc = loc;
		for (j = 0; j < width; j++)
		{
			row_loc[j] |= (bitmap[i * width + j] >> (x & 15));
			row_loc[j + 1] |= (bitmap[i * width + j] << (16 - (x & 15)));
		}
		loc += 40;
	}
}

/*
----- FUNCTION: plot_bitmap_8 -----
Purpose: plots an unsigned char bitmap size onto the screen
		 with a given (x,y) coordinate

Parameters: UINT8 base 				(unsigned char pointer to frame buffer)
			int x 					(user horizontal position)
			int y 					(user vertical position)
			const 					INT8 bitmap (bitmap array address)
			unsigned char height 	(height of the bitmap array)

Assumptions: Can only pass a bitmap, height, and frame buffer pointer that is
			 strictly for unsigned char size.
			 Must be plotted within the 640 x 400 boundaries otherwise doesn't plot anything.
*/
void plot_bitmap_8(UINT8 *base, int x, int y,
				   const UINT8 *bitmap, unsigned char height)
{
	UINT8 *loc = (base + y * 80 + (x >> 3));
	int i;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		for (i = 0; i < height; i++)
		{
			*loc = bitmap[i] >> (x & 7);
			*(loc + 1) = bitmap[i] << 8 - (x & 7);
			loc += 80;
		}
	}
}
