
	#include <stdio.h>

	int
main (void)
{
	char	ligne [128];
	int	i;

	fprintf (stdout, "Entrez un entier : ");
	fgets (ligne, 128, stdin);
	if (sscanf (ligne, "%d\n", & i) == 1)
		fprintf (stdout, "Ok i=%d\n", i);
	else
		fprintf (stdout, "Erreur\n");
	return (0);
}
