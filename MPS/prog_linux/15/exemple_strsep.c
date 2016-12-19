
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#define LG_MAXI	256

	int
main (void)
{
	char	* ligne;
	char	* champs;
	int	l, c;
	char	* pointeur;

	if ((ligne = (char *) malloc (LG_MAXI)) == NULL) {
		perror ("malloc");
		exit (1);
	}

	l = 1;

	while (fgets (ligne, LG_MAXI, stdin) != NULL) {
		fprintf (stdout, "Ligne %d\n", l);

		c = 1;
		pointeur = ligne;
		while (1) {
			champs = strsep (& pointeur, " \t");
			if (champs == NULL)
				break;
			if (champs [0] == '\0')
				continue;
			fprintf (stdout, "  champs %d : %s\n", c, champs);
			c ++;
		}
		l ++;
	}

	return (0);
}
