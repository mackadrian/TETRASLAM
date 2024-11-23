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
	plot_bitmap_16(base_16, 0, 0, I_piece, 64, 1);
	plot_bitmap_16(base_16, 15, 0, I_piece, 64, 1);
	plot_bitmap_16(base_16, 2, 0, I_piece, 64, 1);
	plot_bitmap_16(base_16, 640 - 32, 0, J_piece, 48, 2);
	plot_bitmap_16(base_16, 0, 323, L_piece, 48, 2);
	plot_bitmap_16(base_16, 640 - 32, 323, O_piece, 32, 2);
	plot_bitmap_16(base_16, 225, 200, tile, 16, 1);
	Cnecin();
	clear_screen(base_32);

	Cnecin();
	/* Test 2: test for overlapping */
	plot_bitmap_16(base_16, 0, 0, J_piece, 48, 2);
	plot_bitmap_16(base_16, 16, 0, L_piece, 48, 2);
	plot_bitmap_16(base_16, 32, 0, J_piece, 48, 2);
	plot_bitmap_16(base_16, 48, 0, L_piece, 48, 2);
	plot_bitmap_16(base_16, 64, 0, J_piece, 48, 2);
	plot_bitmap_16(base_16, 80, 0, L_piece, 48, 2);

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
	plot_bitmap_16(base_16, 224, 32, playing_field, 320, 10);
	plot_text(base_8, 384 + 16, 32, font, "C O U N T E R:");
	plot_text(base_8, 384 + 16, 32 + 16, font, "1 0 0  /  1 0 0");

	plot_bitmap_16(base_16, 288, 32, I_piece, 64, 1);
	plot_bitmap_16(base_16, 224, 112, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + 16, 112, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 3), 112, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 4), 112, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 5), 112, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 6), 112, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 8), 112, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 9), 112, tile, 16, 1);
	plot_bitmap_16(base_16, 224, 112, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + 16, 112 + 16, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 3), 112 + 16, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 4), 112 + 16, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 5), 112 + 16, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 6), 112 + 16, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 8), 112 + 16, tile, 16, 1);
	plot_bitmap_16(base_16, 224 + (16 * 9), 112 + 16, tile, 16, 1);

	Cnecin();
	/*Test 6: clearing tiles*/
	clear_bitmap_16(base_16, 224, 112, tile, 16, 1);
	clear_bitmap_16(base_16, 224 + 16, 112, tile, 16, 1);
	clear_bitmap_16(base_16, 224 + (16 * 3), 112, tile, 16, 1);
	clear_bitmap_16(base_16, 224 + (16 * 4), 112, tile, 16, 1);
	clear_bitmap_16(base_16, 224 + (16 * 5), 112, tile, 16, 1);
	clear_bitmap_16(base_16, 224 + (16 * 6), 112, tile, 16, 1);
	clear_bitmap_16(base_16, 224 + (16 * 8), 112, tile, 16, 1);
	clear_bitmap_16(base_16, 224 + (16 * 9), 112, tile, 16, 1);
	clear_bitmap_row_16(base_16, 224, 112 + 16, tile, 16, 1);

	Cnecin();
	clear_screen(base_32);
	return 0;
}
