#include <osbind.h>
#include "raster.h"
#include <stdio.h>

#define HEIGHT 16
const UINT16 test[HEIGHT] = {
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF,
	0xFFFF};

int main()
{
	UINT16 *base_16 = (UINT16 *)Physbase();

	printf("\ffff");
	/* Test 1: plot at 0,0. */
	Cnecin();
	plot_bitmap_16(base_16, 0, 0, test, HEIGHT);
	Cnecin();

	return 0;
}
