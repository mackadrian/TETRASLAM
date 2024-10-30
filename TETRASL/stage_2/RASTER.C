/**
 * @file RASTER.C
 * @brief contains all of the plotting routines for plotting bitmaps.
 * @author Mack Bautista
 */

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
			unsigned int height 	height of the bitmap
			unsigned int width 		width of the bitmap

Assumptions: - Can only pass a bitmap, height, and frame buffer pointer that is
			   strictly for unsigned int size.
			 - Plot within 640 x 400 screen size.



*/
void plot_bitmap_16(UINT16 *base, int x, int y,
					const UINT16 *bitmap,
					unsigned int height, unsigned int width)
{
	int i, j;
	int shift = x & 15;
	UINT16 *loc = base + y * 40 + (x >> 4);
	for (i = 0; i < height; i++)
	{
		const UINT16 *current_row = bitmap + (i * width);
		UINT16 *current_loc = loc;
		for (j = 0; j < width; j++)
		{
			*current_loc |= (current_row[j] >> shift);
			*(current_loc + 1) |= (current_row[j] << (16 - shift));
			current_loc++;
		}
		loc += 40;
	}
}

/*
----- FUNCTION: clear_bitmap_16 -----
Purpose: clears bitmap at a specified coordinate position with a given width
		 and height

Parameters: UINT16 base 			pointer to frame buffer
			int x 					horizontal position
			int y 					vertical position
			unsigned int height		height of bitmap
			unsigned int width		width of bitmap

Assumptions: - Must know the size and position of the bitmap that is being cleared.
			 - Tile collision at playing field border creates 2 thick lines at edge of collision.
*/
void clear_bitmap_16(UINT16 *base, int x, int y,
					 const UINT16 *bitmap,
					 unsigned int height, unsigned int width)
{
	int i, j;
	int shift = x & 15;
	UINT16 *loc = base + y * 40 + (x >> 4);
	UINT16 left_mask = 0xffff << (16 - shift);
	UINT16 right_mask = 0xffff >> shift;

	for (i = 0; i < height; i++)
	{
		const UINT16 *current_row = bitmap + (i * width);
		UINT16 *current_loc = loc;
		for (j = 0; j < width; j++)
		{
			if (shift == 0)
			{
				loc[j] = current_row[j];
			}
			else
			{
				loc[j] = (loc[j] & left_mask) | (current_row[j] >> shift);
				loc[j + 1] = (loc[j + 1] & right_mask) | (current_row[j] << (16 - shift));
			}
		}
		loc += 40;
	}
}

/*
----- FUNCTION: clear_bitmap_row_16 -----
Purpose: clears a row of bitmap specified at the coordinate position

Parameters: UINT16 base 			pointer to frame buffer
			int x 					horizontal position
			int y 					vertical position
			unsigned int height		height of the row
			unsigned int width		column starting from 225 to 360

Assumptions: - Must know the size and position of the bitmap that is being cleared.
			 - Tile collision at playing field border creates 2 thick lines at edge of collision.
*/
void clear_bitmap_row_16(UINT16 *base, int x, int y,
						 const UINT16 *bitmap,
						 unsigned int height, unsigned int width)
{
	int i, j;

	for (i = 0; i < height; i++)
	{
		for (j = x; j <= 360; j += 15)
		{
			clear_bitmap_16(base, j, y, bitmap, 16, 1);
		}
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
	int i, index;
	int shift = x & 7;
	UINT8 *loc = base + y * 80 + (x >> 3);
	index = ascii - 32;

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
Purpose: plots a string text to the screen

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

/*
----- FUNCTION: clear_char -----
Purpose: clears a desired character text from the screen

Parameters: UINT8 base 				unsigned char pointer to frame buffer
			int x 					user horizontal position
			int y 					user vertical position

Assumptions: - Can only pass a frame buffer pointer that is
			  strictly for unsigned char size.
			 - Must be within the 640 x 400 boundaries; otherwise, nothing is cleared.
*/
void clear_char(UINT8 *base, int x, int y)
{
	int i;
	UINT8 *loc = base + y * 80 + (x >> 3);

	for (i = 0; i < 8; i++)
	{
		*loc = 0;
		loc += 80;
	}
}

/*
----- FUNCTION: clear_text -----
Purpose: clears a string text from the screen

Parameters: UINT8 base 				unsigned char pointer to frame buffer
			int x 					user horizontal position
			int y 					user vertical position
			int length              length of the string to clear

Assumptions: - Can only pass a frame buffer pointer that is
			  strictly for unsigned char size.
			 - Must be within the 640 x 400 boundaries; otherwise, nothing is cleared.
*/
void clear_text(UINT8 *base, int x, int y, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		clear_char(base, x + (i * 8), y);
	}
}