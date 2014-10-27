
	#include <math.h>
	#include <stdio.h>


	int
main (void)
{
	double	d;
	double	arrondi_inf;
	double	arrondi_sup;
	double	arrondi_proche;
	int	converti;

	printf ("réel    floor() ceil()  rint()  (int)\n");
	for (d = -1.8; d < 1.9; d += 0.1) {
		arrondi_inf = floor (d);
		arrondi_sup = ceil (d);
		arrondi_proche = rint (d);
		converti = (int) d;
		printf ("% 4.1f    % 4.1f    % 4.1f    % 4.1f    % 2d\n",
			d, arrondi_inf, arrondi_sup, arrondi_proche, converti);
	}
	return (0);
}
