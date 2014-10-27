
	#include <stdio.h>

	int
main (void)
{
	fprintf (stdout, "Cette ligne est envoyée sur la sortie normale\n");
	if (freopen ("essai.freopen", "w", stdout) == NULL) {
		perror ("freopen");
		exit (1);
	}
	fprintf (stdout, "Cette ligne doit se trouver dans le fichier\n");
	return (0);
}

