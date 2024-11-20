/**
 * @file TST_RAST.C
 * @brief tests the raster plotting routines by plotting images required for the game.
 * @author Mack Bautista
 */
#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "bitmaps.h"
#include "font.h"

int main()
{
	int i, j, row, col;
	UINT32 *base_32 = (UINT32 *)Physbase();
	UINT16 *base_16 = (UINT16 *)Physbase();
	UINT8 *base_8 = (UINT8 *)Physbase();

	printf("\033E\033f\n");
	clear_screen(base_32);
	Cnecin();
	/* Test 1: plot at each boundary corner */
	plot_bitmap_16(base_16, 0, 0, I_piece, 61, 1);
	plot_bitmap_16(base_16, 639 - 16, 0, I_piece, 61, 1);
	plot_bitmap_16(base_16, 0, 323, I_piece, 61, 1);
	plot_bitmap_16(base_16, 639 - 16, 323, I_piece, 61, 1);
	plot_bitmap_16(base_16, 225, 200, tile, 16, 1);
	Cnecin();
	clear_screen(base_32);

	Cnecin();
	/*Test 2: plot overlapping pieces*/
	plot_bitmap_16(base_16, 0, 0, J_piece, 46, 2);
	plot_bitmap_16(base_16, 1, 0, L_piece, 46, 2);
	plot_bitmap_16(base_16, 2, 0, L_piece, 46, 2);
	plot_bitmap_16(base_16, 3, 0, L_piece, 46, 2);
	plot_bitmap_16(base_16, 4, 0, L_piece, 46, 2);
	plot_bitmap_16(base_16, 320, 200, J_piece, 46, 2);
	plot_bitmap_16(base_16, 320 + (2 * 15), 200, I_piece, 61, 1);
	plot_bitmap_16(base_16, 320, 200 + 60, O_piece, 31, 2);
	plot_bitmap_16(base_16, 300, 300, S_piece, 31, 3);
	plot_bitmap_16(base_16, 255, 300, T_piece, 31, 3);
	plot_bitmap_16(base_16, 300 - 89, 300, Z_piece, 31, 3);

	Cnecin();
	clear_screen(base_32);

	Cnecin();
	/*Test 3: plotting text*/
	plot_char(base_8, 0, 0, font, 'H');
	plot_char(base_8, 8, 0, font, 'E');
	plot_char(base_8, 16, 0, font, 'L');
	plot_char(base_8, 24, 0, font, 'L');
	plot_char(base_8, 32, 0, font, 'O');
	plot_text(base_8, 320, 200, font, "C O U N T E R:");
	plot_text(base_8, 320, 200 + 8, font, "1 0 0  /  1 0 0");
	Cnecin();
	/*Test 4: clearing char*/
	clear_char(base_8, 0, 0);
	clear_char(base_8, 8, 0);
	clear_char(base_8, 16, 0);
	clear_char(base_8, 24, 0);
	clear_char(base_8, 32, 0);
	clear_text(base_8, 320, 200, 14);
	clear_text(base_8, 320, 200 + 8, 10);

	Cnecin();
	clear_screen(base_32);

	/*Test 5: plot initial game state*/
	Cnecin();
	plot_bitmap_16(base_16, 224, 40, playing_field, 303, 10);
	plot_text(base_8, 329 + (48 * 2), 40, font, "C O U N T E R:");
	plot_text(base_8, 329 + (48 * 2), 40 + 8, font, "1 0 0  /  1 0 0");

	plot_bitmap_16(base_16, 225, 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 225 + 15, 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 2), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 3), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 4), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 5), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 6), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 7), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 8), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 9), 41 + (15 * 4), tile, 16, 1);

	plot_bitmap_16(base_16, 255, 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 255 + (15 * 2), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 255 + (15 * 3), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 255 + (15 * 6), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 255 + (15 * 7), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 255 + 15, 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 255 + (15 * 5), 41 + (15 * 4), tile, 16, 1);
	plot_bitmap_16(base_16, 255 + (15 * 4), 41 + (15 * 4), tile, 16, 1);

	plot_bitmap_16(base_16, 225, 281, I_piece, 61, 1);
	plot_bitmap_16(base_16, 225, 236, J_piece, 46, 2);
	Cnecin();

	plot_bitmap_16(base_16, 285, 41, tile, 16, 1);
	plot_bitmap_16(base_16, 285, 56, tile, 16, 1);
	plot_bitmap_16(base_16, 285, 71, tile, 16, 1);
	plot_bitmap_16(base_16, 285, 86, tile, 16, 1);
	plot_bitmap_16(base_16, 225, 281, tile, 16, 1);
	plot_bitmap_16(base_16, 225, 296, tile, 16, 1);
	plot_bitmap_16(base_16, 225, 311, tile, 16, 1);
	plot_bitmap_16(base_16, 225, 326, tile, 16, 1);
	plot_bitmap_16(base_16, 360, 41, tile, 16, 1);
	plot_bitmap_16(base_16, 360, 56, tile, 16, 1);
	plot_bitmap_16(base_16, 360, 71, tile, 16, 1);
	plot_bitmap_16(base_16, 360, 86, tile, 16, 1);

	Cnecin();

	clear_bitmap_row_16(base_16, 225, 41 + (15 * 4), clear_tile, 16, 135);

	/*Test 6: clear tiles*/
	clear_bitmap_16(base_16, 285, 41, clear_tile, 16, 1);
	clear_bitmap_16(base_16, 285, 56, clear_tile, 16, 1);
	clear_bitmap_16(base_16, 285, 71, clear_tile, 16, 1);
	clear_bitmap_16(base_16, 285, 86, clear_tile, 16, 1);
	clear_bitmap_16(base_16, 225, 281, clear_tile, 16, 1);
	clear_bitmap_16(base_16, 225, 296, clear_tile, 16, 1);
	clear_bitmap_16(base_16, 225, 311, clear_tile, 16, 1);
	clear_bitmap_16(base_16, 225, 326, clear_tile, 16, 1);
	clear_bitmap_16(base_16, 360, 41, clear_tile, 16, 1);
	clear_bitmap_16(base_16, 360, 56, clear_tile, 16, 1);
	clear_bitmap_16(base_16, 360, 71, clear_tile, 16, 1);
	clear_bitmap_16(base_16, 360, 86, clear_tile, 16, 1);

	Cnecin();
	clear_screen(base_32);
	return 0;
}
