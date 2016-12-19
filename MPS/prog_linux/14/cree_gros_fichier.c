
	#include <stdio.h>
	#include <stdlib.h>

	#define TAILLE_BLOC	(1024 * 1024)

	int
main (int argc, char * argv [])
{
	int	nombre_blocs;
	FILE *	fp;
	char *	bloc;
	int	i;

	if ((argc != 3) || (sscanf (argv [2], "%d", & nombre_blocs) != 1)) {
		fprintf (stderr, "Syntaxe : %s fichier nb_blocs\n", argv [0]);
		exit (1);
	}
	if ((fp = fopen (argv [1], "w")) == NULL) {
		perror ("fopen");
		exit (1);
	}
	if ((bloc = malloc (TAILLE_BLOC)) == NULL) {
		perror ("malloc");
		exit (1);
	}
	for (i = 0 ; i < nombre_blocs; i ++) {
		memset (bloc, i, TAILLE_BLOC);
		if (fwrite (bloc, 1, TAILLE_BLOC, fp) != TAILLE_BLOC) {
			perror ("fwrite");
			exit (1);
		}
	}
	fclose (fp);
	return (0);
}
