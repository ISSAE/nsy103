
	#include <math.h>
	#include <stdio.h>


	int
main (void)
{
	double e;

	e = cos (M_PI / 4) * 2.0;
	e = e * e - 2.0;
	fprintf (stdout, "(2 * cos (PI/4))²-2 = %e\n", e);
	return (0);
}
