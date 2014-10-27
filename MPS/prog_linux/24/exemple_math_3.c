
	#include <errno.h>
	#include <math.h>
	#include <stdio.h>
	#include <string.h>


	void
affiche_nombre (const char * chaine, double d)
{
	fprintf (stdout, "%s", chaine);
	if (isnan (d))
		fprintf (stdout, "Indéfini\n");
	else if (isinf (d) == 1)
		fprintf (stdout, "+ Infini\n");
	else if (isinf (d) == -1)
		fprintf (stdout, "- Infini\n");
	else
		fprintf (stdout, "%f\n", d);
}

	int
main (void)
{
	double	d;

	d = +0.0;
	d = 1.0 / d;
	affiche_nombre ("1 / +0 = ", d);
	d = -0.0;
	d = 1.0 / d;
	affiche_nombre ("1 / -0 = ", d);
	d = 0.0 / 0.0;
	affiche_nombre ("0 / 0 = ", d);
	d = log (0.0);
	affiche_nombre ("log (0) = ", d);
	d = log (-1.0);
	affiche_nombre ("log (-1)= ", d);
	d = FLT_MAX;
	affiche_nombre ("FLT_MAX = ", d);
	d = exp (FLT_MAX);
	affiche_nombre ("exp(FLT_MAX)= ", d);
	return (0);
}
