/**
 * @file TST_RAST.C
 * @brief tests the raster plotting routines by plotting images required for the game.
 * @author Mack Bautista
 */
#include <osbind.h>
#include "raster.h"
#include "bitmaps.h" /*temporary*/
#include "font.h"

int main()
{
	int i, j;
	UINT32 *base_32 = (UINT32 *)Physbase();
	UINT16 *base_16 = (UINT16 *)Physbase();
	UINT8 *base_8 = (UINT8 *)Physbase();

	/* Set screen to white.*/
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
	plot_bitmap_16(base_16, 30, 0, L_piece, 46, 2);
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
	Cnecin();
	plot_text(base_8, 320, 200, font, "C O U N T E R:");
	plot_text(base_8, 320, 200 + 8, font, "1 0 0  /  1 0 0");

	Cnecin();
	clear_screen(base_32);

	Cnecin();
	/*Test 5: playing field*/
	plot_bitmap_16(base_16, 176, 40, playing_field, 303, 10);
	Cnecin();

	clear_screen(base_32);

	/*Test 6: plot tiles*/
	Cnecin();
	plot_bitmap_16(base_16, 224, 40, playing_field, 303, 10);
	plot_bitmap_16(base_16, 225, 41, tile, 16, 1);
	plot_bitmap_16(base_16, 225 + 15, 41, tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 2), 41, tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 3), 41, tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 4), 41, tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 5), 41, tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 6), 41, tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 7), 41, tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 8), 41, tile, 16, 1);
	plot_bitmap_16(base_16, 225 + (15 * 9), 41, tile, 16, 1);
	plot_text(base_8, 329 + (48 * 2), 40, font, "C O U N T E R:");
	plot_text(base_8, 329 + (48 * 2), 40 + 8, font, "1 0 0  /  1 0 0");

	Cnecin();
	clear_tile(base_16, 225, 41, 15);
	clear_tile(base_16, 225 + 15, 41, 15);

	Cnecin();
	/*STAGE 3 -> Test 2: dropping I_piece at left boundary...
	plot_bitmap_16(base_16, 225, 281, I_piece, 61, 1);
	Cnecin();
	plot_bitmap_16(base_16, 225, 281, tile, 16, 1);
	plot_bitmap_16(base_16, 225, 296, tile, 16, 1);
	plot_bitmap_16(base_16, 225, 311, tile, 16, 1);
	plot_bitmap_16(base_16, 225, 326, tile, 16, 1);

	Cnecin();
	STAGE 3 -> Test 3: dropping I_piece at right boundary...
	plot_bitmap_16(base_16, 360, 71, I_piece, 61, 1);
	Cnecin();
	plot_bitmap_16(base_16, 360, 71, tile, 16, 1);
	plot_bitmap_16(base_16, 360, 86, tile, 16, 1);
	plot_bitmap_16(base_16, 360, 101, tile, 16, 1);
	plot_bitmap_16(base_16, 360, 116, tile, 16, 1);

	Cnecin();
	STAGE 3 -> Test 4: dropping I_piece at starting column...
	plot_bitmap_16(base_16, 285, 86, I_piece, 61, 1);
	Cnecin();
	plot_bitmap_16(base_16, 285, 86, tile, 16, 1);
	plot_bitmap_16(base_16, 285, 101, tile, 16, 1);
	plot_bitmap_16(base_16, 285, 116, tile, 16, 1);
	plot_bitmap_16(base_16, 285, 131, tile, 16, 1);

	Cnecin();
	STAGE 3 -> Test 6: dropping I_piece at next available column...
	plot_bitmap_16(base_16, 300, 281, I_piece, 61, 1);
	Cnecin();
	plot_bitmap_16(base_16, 300, 281, tile, 16, 1);
	plot_bitmap_16(base_16, 300, 296, tile, 16, 1);
	plot_bitmap_16(base_16, 300, 311, tile, 16, 1);
	plot_bitmap_16(base_16, 300, 326, tile, 16, 1);

	STAGE 3 -> Test 6 (continued): Filling up next column...
	plot_bitmap_16(base_16, 300, 221, I_piece, 61, 1);
	plot_bitmap_16(base_16, 300, 161, I_piece, 61, 1);
	plot_bitmap_16(base_16, 300, 101, I_piece, 61, 1);
	Cnecin();
	plot_bitmap_16(base_16, 315, 86, I_piece, 61, 1);

	Cnecin();
	STAGE 3 -> Test 7: Cycle to J_piece...
	plot_bitmap_16(base_16, 330, 56, I_piece, 61, 1);

	Cnecin();
	STAGE 3 -> Test 8: Dropping J_piece...
	plot_bitmap_16(base_16, 255, 101, J_piece, 46, 2);
	plot_bitmap_16(base_16, 345, 41, J_piece, 46, 2);

	uncomment to test how each piece is generated at the top
	plot_bitmap_16(base_16, 225 + (15 * 4), 41, J_piece, 46, 2);
	plot_bitmap_16(base_16, 225 + (15 * 4), 41, L_piece, 46, 2);
	plot_bitmap_16(base_16, 225 + (15 * 4), 41, O_piece, 31, 2);
	plot_bitmap_16(base_16, 225 + (15 * 4), 41, S_piece, 31, 3);
	plot_bitmap_16(base_16, 225 + (15 * 4), 41, T_piece, 31, 3);
	plot_bitmap_16(base_16, 225 + (15 * 4), 41, Z_piece, 31, 3);
	*/

	Cnecin();
	clear_screen(base_32);
	return 0;
}
