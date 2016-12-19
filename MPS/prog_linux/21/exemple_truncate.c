
	#include <stdio.h>
	#include <unistd.h>

	int
main (int argc, char * argv [])
{
	long longueur;
	if ((argc != 3) || (sscanf (argv [2], "%ld", & longueur) != 1)) {
		fprintf (stderr, "Syntaxe : %s fichier longueur\n", argv [0]);
		exit (1);
	}
	if (truncate (argv [1], longueur) < 0)
		perror (argv [1]);
	return (0);
}
