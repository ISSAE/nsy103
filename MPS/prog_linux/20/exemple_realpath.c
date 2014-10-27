	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/param.h>

	int
main (int argc, char * argv [])
{
	char chemin_complet [MAXPATHLEN];
	int i;

	for (i = 0; i < argc; i ++) {
		fprintf (stderr, "%s : ", argv [i]);
		if (realpath (argv [i], chemin_complet) == NULL)
			perror ("");
		else
			fprintf (stderr, "%s\n", chemin_complet);
	}
	return (0);
}
