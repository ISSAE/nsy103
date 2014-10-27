
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

	if ((ligne = (char *) malloc (LG_MAXI)) == NULL) {
		perror ("malloc");
		exit (1);
	}

	l = 1;

	while (fgets (ligne, LG_MAXI, stdin) != NULL) {
		fprintf (stdout, "Ligne %d\n", l);

		c = 1;
		champs = strtok (ligne, " \t");
		while (champs != NULL) { 
			fprintf (stdout, "  champs %d : %s\n", c, champs);
			champs = strtok (NULL, " \t");
			c ++;
		}
		l ++;
	}

	return (0);
}
