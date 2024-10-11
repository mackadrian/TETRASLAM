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

	return 0;
}
