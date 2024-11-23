/**
 * @file RASTER.C
 * @brief contains all of the plotting routines for plotting bitmaps.
 * @author Mack Bautista
 */

#include "raster.h"

#define PIXELS_PER_SCREEN 256000
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

/*
----- FUNCTION: clear_screen -----
Purpose: Clears all the pixels on the screen by setting all memory locations in the
		 frame buffer to 0.

Parameters:
  - UINT32 *base: Pointer to the frame buffer where the pixels will be cleared.
				  The base address must point to a memory area for unsigned integers.

Details:
  - The function operates strictly within the boundaries of a 640 x 400 screen.
  - The frame buffer is expected to use unsigned integers for storage, and the
	function clears all 32-bit pixels sequentially.
  - Each iteration clears four pixels at a time for efficiency.

Limitations:
  - The function does not perform bounds checking; ensure the buffer size matches
	the screen resolution.
*/
void clear_screen(UINT32 *base)
{
	UINT32 *start = base;
	UINT32 *end = start + (PIXELS_PER_SCREEN >> 5);
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
Purpose: Plots a bitmap onto the screen at a given (x, y) coordinate.

Details:
  - The bitmap width must be word-aligned when the base is an unsigned int pointer.
  - The bitmap width is assumed to be byte-aligned when the base is an unsigned char pointer.
  - The bitmap is plotted within the 640 x 400 screen boundaries using the specified
	height and width.
  - This function performs a bitwise OR operation to plot the bitmap onto the screen.

Parameters:
  - UINT16 *base: Pointer to the frame buffer where the bitmap will be plotted.
  - int x: Horizontal position of the bitmap.
  - int y: Vertical position of the bitmap.
  - const UINT16 *bitmap: Pointer to the bitmap array to be plotted.
  - unsigned int height: Height of the bitmap in pixels.
  - unsigned int width: Width of the bitmap in pixels.

Assumptions:
  - The x and y coordinates must result in a bitmap that fits within the screen size.
  - Proper word alignment is required for bitmaps when using an unsigned int frame buffer.
  - Shifts are applied to account for misaligned x positions.
*/
void plot_bitmap_16(UINT16 *base, int x, int y,
					const UINT16 *bitmap,
					unsigned int height, unsigned int width)
{
	int i, j;
	UINT16 *loc = base + y * 40 + (x >> 4);

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}

	for (i = 0; i < height; i++)
	{
		const UINT16 *current_row = bitmap + (i * width);
		for (j = 0; j < width; j++)
		{
			loc[j] |= current_row[j];
		}

		loc += 40;
	}
}

/*
----- FUNCTION: clear_bitmap_16 -----
Purpose: Clears a bitmap at a specified coordinate position with a given width and height.

Details:
	- The function handles both aligned and shifted bitmap placements.
	- A shift value (based on the x position) determines how the bitmap rows align with the frame buffer.
	- Left and right masks are used to clear partial overlaps at the boundaries.
	- The frame buffer width is assumed to be 640 pixels, divided into 40 UINT16 words per row.
	- This function performs a bitwise AND operation with the negation of the bitmap to clear the pixels.

Parameters:
	- UINT16 *base: Pointer to the frame buffer.
	- int x: Horizontal position.
	- int y: Vertical position.
	- const UINT16 *bitmap: Pointer to the bitmap to be cleared.
	- unsigned int height: Height of the bitmap.
	- unsigned int width: Width of the bitmap.

Assumptions:
	- Must know the size and position of the bitmap that is being cleared.
	- Tile collision at the playing field border creates 2 thick lines at the edge of the collision.
	- Must operate within the 640 x 400 boundaries; otherwise, behavior is undefined.
*/
void clear_bitmap_16(UINT16 *base, int x, int y,
					 const UINT16 *bitmap,
					 unsigned int height, unsigned int width)
{
	int i, j;
	UINT16 *loc = base + y * 40 + (x >> 4);

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}

	for (i = 0; i < height; i++)
	{
		const UINT16 *current_row = bitmap + (i * width);
		for (j = 0; j < width; j++)
		{
			loc[j] &= ~current_row[j];
		}

		loc += 40;
	}
}

/*
----- FUNCTION: clear_bitmap_row_16 -----
Purpose: Clears a row of bitmaps specified at the coordinate position.

Details:
	- The function clears bitmaps in a row by iterating through horizontal positions.
	- It uses the clear_bitmap_16 function to clear each segment of the row.
	- Row clearing is done in increments of 16 pixels, handling full-width row clearing for each segment.
	- This function ensures the bitmap is cleared in a specific column range from `x` to `x + (16 * 10)`.

Parameters:
	- UINT16 *base: Pointer to the frame buffer.
	- int x: Horizontal position.
	- int y: Vertical position.
	- const UINT16 *bitmap: Pointer to the bitmap to be cleared.
	- unsigned int height: Height of the row.
	- unsigned int width: Column range, starting from `x` to `x + (16 * 10)`.

Assumptions:
	- Must know the size and position of the bitmap that is being cleared.
	- Tile collision at the playing field border creates 2 thick lines at the edge of the collision.
	- Must operate within the 640 x 400 boundaries; otherwise, behavior is undefined.
*/
void clear_bitmap_row_16(UINT16 *base, int x, int y,
						 const UINT16 *bitmap,
						 unsigned int height, unsigned int width)
{
	int i, j;

	for (i = 0; i < height; i++)
	{
		for (j = x; j <= x + (16 * 10); j += 16)
		{
			clear_bitmap_16(base, j, y, bitmap, height, width);
		}
	}
}

/*
----- FUNCTION: plot_char -----
Purpose: Plots a single character onto the screen at a specified (x, y) position
		 using a font array.

Details:
  - The font array provides the bitmap for each character, indexed by the ASCII value.
  - Each character is 8 pixels wide and assumes byte-aligned widths.
  - The x position must be byte-aligned for accurate plotting.

Parameters:
  - UINT8 *base: Pointer to the frame buffer where the character will be plotted.
  - int x: Horizontal position.
  - int y: Vertical position.
  - const UINT8 *font: Pointer to the font array.
  - int ascii: ASCII value of the character to plot.

Assumptions:
  - Characters are plotted within the 640 x 400 screen size.
  - The font array is indexed starting at ASCII 32.
*/
void plot_char(UINT8 *base, int x, int y,
			   const UINT8 *font, int ascii)
{
	int i, index, shift;
	UINT8 *loc = base + y * 80 + (x >> 3);
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}

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
Purpose: Plots a string of characters onto the screen at a specified starting
		 (x, y) position using a font array.

Details:
  - Each character is plotted sequentially using the plot_char function.
  - Characters are spaced 8 pixels apart horizontally.

Parameters:
  - UINT8 *base: Pointer to the frame buffer where the text will be plotted.
  - int x: Horizontal starting position.
  - int y: Vertical starting position.
  - const UINT8 *font: Pointer to the font array.
  - const char *text: String of characters to plot.

Assumptions:
  - Text is plotted within the 640 x 400 screen size.
  - The font array is indexed starting at ASCII 32.
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
Purpose: Clears a desired character text from the screen.

Details:
	- The function clears an 8x8 character block at the specified screen coordinates.
	- Each character cell spans 8 pixels horizontally.
	- The frame buffer width is assumed to be 640 pixels, divided into 80 bytes per row.

Parameters:
	- UINT8 *base: unsigned char pointer to frame buffer.
	- int x: user horizontal position.
	- int y: user vertical position.

Assumptions:
	- Can only pass a frame buffer pointer that is strictly for unsigned char size.
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
Purpose: Clears a string of text from the screen.

Details:
	- The function iteratively clears characters along a single row.
	- Each character is cleared using the clear_char function.
	- Character width is fixed at 8 pixels.

Parameters:
	- UINT8 *base: unsigned char pointer to frame buffer.
	- int x: user horizontal position.
	- int y: user vertical position.
	- int length: length of the string to clear.

Assumptions:
	- Can only pass a frame buffer pointer that is strictly for unsigned char size.
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
