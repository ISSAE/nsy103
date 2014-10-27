
	#include <stdio.h>

	int
main (void)
{
	int	i;

	fprintf (stdout, "Entrez un entier : ");
	if (scanf ("%d\n", & i) == 1)
		fprintf (stdout, "Ok i=%d\n", i);
	else
		fprintf (stdout, "Erreur\n");
	return (0);
}
