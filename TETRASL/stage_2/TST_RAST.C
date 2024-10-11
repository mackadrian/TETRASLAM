#include <osbind.h>
#include "raster.h"
#include "bitmaps.h"

int main()
{
	int i;
	UINT16 *base_16 = (UINT16 *)Physbase();
	UINT8 *base_8 = (UINT8 *)Physbase();

	/* Set screen to white.*/
	printf("\033E\033f\n");
	clear_screen(base_16);
	Cnecin();
	/* Test 1: plot at at left upper corner boundary */
	plot_bitmap_16(base_16, 0, 0, I_piece, 61, 1);
	/*Test 2: plot at the right upper corner boundary*/
	plot_bitmap_16(base_16, 639 - 16, 0, I_piece, 61, 1);
	/*Test 3: plot at the left bottom corner boundary*/
	plot_bitmap_16(base_16, 0, 323, I_piece, 61, 1);
	/*Test 4: plot at the right bottom corner boundary*/
	plot_bitmap_16(base_16, 639 - 16, 323, I_piece, 61, 1);
	Cnecin();
	clear_screen(base_16);

	Cnecin();
	/*Test 5: overlapping pixels*/
	plot_bitmap_16(base_16, 0, 0, J_piece, 46, 2);
	plot_bitmap_16(base_16, 30, 0, L_piece, 46, 2);
	plot_bitmap_16(base_16, 320, 200, J_piece, 46, 2);
	plot_bitmap_16(base_16, 320 + (2 * 15), 200, I_piece, 61, 1);

	/*Test 6: plotting fonts*/

	return 0;
}
