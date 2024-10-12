#include "raster.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTES_PER_SCREEN 256000

/*
----- FUNCTION: clear_screen -----
Purpose: clears all the pixels in the screen

Parameters: UINT16 base		unsigned int pointer to frame buffer

Limitations: Can only pass a bitmap, height, and frame buffer pointer that is
			 strictly for unsigned int size.
			 Must be plotted within the 640 x 400 boundaries otherwise doesn't plot anything.



*/
void clear_screen(UINT32 *base)
{
	UINT32 *start = base;
	UINT32 *end = start + (BYTES_PER_SCREEN / 32);
	while (start < end)
	{
		*start++ = 0x00000000;
		*start++ = 0x00000000;
		*start++ = 0x00000000;
		*start++ = 0x00000000;
	}
}

/*
----- FUNCTION: plot_bitmap_16 -----
Purpose: plots an unsigned int bitmap size onto the screen
		 with a given (x,y) coordinate

Parameters: UINT16 base				unsigned int pointer to frame buffer
			int x 					horizontal position
			int y 					vertical position
			const UINT16 bitmap 	bitmap array address
			unsigned int height 	height of the bitmap array
			unsigned int width 		width of the bitmap array

Assumptions: - Can only pass a bitmap, height, and frame buffer pointer that is
			   strictly for unsigned int size.
			 - Plot within 640 x 400 screen size.



*/
void plot_bitmap_16(UINT16 *base, int x, int y,
					const UINT16 *bitmap,
					unsigned int height, unsigned int width)
{
	int i, j, shift;
	UINT16 *loc = base + y * 40 + (x >> 4);
	shift = x & 15;
	for (i = 0; i < height; i++)
	{
		const UINT16 *current_row = bitmap + (i * width);
		for (j = 0; j < width; j++)
		{
			loc[j] |= (current_row[j] >> shift);
			loc[j + 1] |= (current_row[j] << (16 - shift));
		}
		loc += 40;
	}
}

/*
----- FUNCTION: plot_bitmap_8 -----
Purpose: plots an unsigned char bitmap size onto the screen
		 with a given (x,y) coordinate

Parameters: UINT8 base 				unsigned char pointer to frame buffer
			int x 					user horizontal position
			int y 					user vertical position
			const UINT8 bitmap 		bitmap array address
			unsigned char height 	height of the bitmap array
			unsigned int width 		width of the bitmap array

Assumptions: - Can only pass a bitmap, height, and frame buffer pointer that is
			 strictly for unsigned char size.
			 - Plot within 640 x 400 screen size.
*/
void plot_bitmap_8(UINT8 *base, int x, int y,
				   const UINT8 *bitmap,
				   unsigned char height, unsigned char width)
{
	int i, j, shift;
	UINT8 *loc = base + y * 80 + (x >> 3);
	shift = x & 7;
	for (i = 0; i < height; i++)
	{
		const UINT8 *current_row = bitmap + (i * width);
		for (j = 0; j < width; j++)
		{
			loc[j] |= (current_row[j] >> shift);
			loc[j + 1] |= (current_row[j] << (8 - shift));
		}
		loc += 80;
	}
}

/*
----- FUNCTION: plot_char -----
Purpose: plots a desired character text to the screen

Parameters: UINT8 base 				unsigned char pointer to frame buffer
			int x 					user horizontal position
			int y 					user vertical position
			const UINT8 font		font array address
			int ascii 				ascii value of char to print

Assumptions: - Can only pass a font, height, and frame buffer pointer that is
			 strictly for unsigned char size.
			 - Must be plotted within the 640 x 400 boundaries otherwise doesn't plot anything.
*/
void plot_char(UINT8 *base, int x, int y,
			   const UINT8 *font, int ascii)
{
	int i, index, shift;
	UINT8 *loc = base + y * 80 + (x >> 3);
	index = ascii - 32;
	shift = x & 7;
	for (i = 0; i < 8; i++)
	{
		UINT8 row = font[index * 8 + i];
		*loc |= (row >> shift);
		*(loc + 1) |= (row << (8 - shift));
		loc += 80;
	}
}

/*
----- FUNCTION: plot_text -----
Purpose: plots a collection of character text to the screen

Parameters: UINT8 base 				unsigned char pointer to frame buffer
			int x 					user horizontal position
			int y 					user vertical position
			const UINT8 font		font array address
			const char 				user string that is printed

Assumptions: - Can only pass a font, height, and frame buffer pointer that is
			 strictly for unsigned char size.
			 - Must be plotted within the 640 x 400 boundaries otherwise doesn't plot anything.
*/
void plot_text(UINT8 *base, int x, int y,
			   const UINT8 *font, const char *text)
{
	while (*text)
	{
		plot_char(base, x, y, font, *text);
		x += 8;
		text++;
	}
}