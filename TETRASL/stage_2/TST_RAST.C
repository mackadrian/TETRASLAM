#include <osbind.h>
#include "raster.h"
#include "font.h"

#define HEIGHT 61
const UINT16 test[HEIGHT] = {
	0xffff,
	0xe007,
	0xf00f,
	0xb81d,
	0x9c39,
	0x8e71,
	0x87e1,
	0x83c1,
	0x83c1,
	0x87e1,
	0x8e71,
	0x9c39,
	0xb81d,
	0xf00f,
	0xe007,
	0xffff,
	0xe007,
	0xf00f,
	0xb81d,
	0x9c39,
	0x8e71,
	0x87e1,
	0x83c1,
	0x83c1,
	0x87e1,
	0x8e71,
	0x9c39,
	0xb81d,
	0xf00f,
	0xe007,
	0xffff,
	0xe007,
	0xf00f,
	0xb81d,
	0x9c39,
	0x8e71,
	0x87e1,
	0x83c1,
	0x83c1,
	0x87e1,
	0x8e71,
	0x9c39,
	0xb81d,
	0xf00f,
	0xe007,
	0xffff,
	0xe007,
	0xf00f,
	0xb81d,
	0x9c39,
	0x8e71,
	0x87e1,
	0x83c1,
	0x83c1,
	0x87e1,
	0x8e71,
	0x9c39,
	0xb81d,
	0xf00f,
	0xe007,
	0xffff};

int main()
{
	UINT16 *base_16 = (UINT16 *)Physbase();
	UINT8 *base_8 = (UINT8 *)Physbase();

	/* Set screen to white.*/
	printf("\033E\033f\n");
	Cnecin();
	/* Test 1: plot at at left upper corner boundary */
	plot_bitmap_16(base_16, 0, 0, test, HEIGHT);
	/*Test 2: plot at the right upper corner boundary*/
	plot_bitmap_16(base_16, 639, 0, test, HEIGHT);
	/*Test 3: plot at the left bottom corner boundary*/
	plot_bitmap_16(base_16, 0, 323, test, HEIGHT);
	/*Test 4: plot at the right bottom corner boundary*/
	plot_bitmap_16(base_16, 639, 323, test, HEIGHT);
	Cnecin();
	clear_screen(base_16);

	Cnecin();
	/*Test 5: overlapping pixels*/
	plot_bitmap_16(base_16, 0, 0, test, HEIGHT);
	Cnecin();
	plot_bitmap_16(base_16, 17, 0, test, HEIGHT);
	Cnecin();
	plot_bitmap_16(base_16, 32, 0, test, HEIGHT);
	Cnecin();
	clear_screen(base_16);

	/*Test 6: plotting fonts*/
	plot_bitmap_8(base_8, 0, 0, font, 8);

	return 0;
}
