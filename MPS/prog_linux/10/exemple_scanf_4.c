
	#include <stdio.h>

	int
main (void)
{
	char	ligne [128];
	int i;

	fprintf (stdout, "Veuillez entrer un entier : ");
	while (1) {
		if (fgets (ligne, 128, stdin) == NULL) {
			fprintf (stderr, "Fin de fichier inattendue\n");
			return (1);
		}
		if (sscanf (ligne, "%d", & i) == 1)
			break;
		fprintf (stdout, "\nErreur, un entier svp : ");
	}
	fprintf (stdout, "Ok\n");
	return (0);
}
