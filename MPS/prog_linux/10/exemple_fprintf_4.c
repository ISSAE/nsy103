	#include <stdio.h>

	int
main (void)
{
	int largeur;
	int precision;

	for (largeur = 1; largeur < 10; largeur ++)
		fprintf (stdout, "|%*d|\n", largeur, largeur);
	for (precision = 0; precision < 10; precision ++)
			fprintf (stdout, "|%.*d|\n", precision, precision);
	return (0);
}


