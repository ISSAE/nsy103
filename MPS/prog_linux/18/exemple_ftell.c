
	#include <stdio.h>

	int
main (void)
{
	long	derniere;
	long	position;
	int	caractere;
	
	position = ftell (stdin);
	if (position == -1) {
		perror ("ftell");
		exit(1);
	}
	derniere = position;
	while ((caractere = getchar ()) != EOF) {

		if (caractere == '\n') {
			position = ftell (stdin);
			if (position == -1) {
				perror ("ftell");
				exit (1);
			}
			fprintf (stdout, "%ld ", position - derniere - 1);
			derniere = position;
		}
	}
	fprintf (stdout, "\n");
	return (0);
}
