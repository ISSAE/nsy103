
	#include <dirent.h>
	#include <fnmatch.h>
	#include <stdio.h>
	#include <stdlib.h>


	static char * motif = NULL;

	int
selection (const struct dirent * entree)
{
	if (fnmatch (motif, entree -> d_name, FNM_PATHNAME | FNM_PERIOD) == 0)
		return (1);
	return (0);
}

	int
main (int argc, char * argv [])
{
	struct dirent ** liste;
	int		 nb_entrees;
	int		 i;

	if (argc != 3) {
		fprintf (stderr, "Syntaxe : %s r�pertoire motif\n", argv [0]);
		exit (1);
	}
	motif = argv [2];
	nb_entrees = scandir (argv [1], & liste, selection, alphasort);
	if (nb_entrees <= 0)
		return (0);
	for (i = 0; i < nb_entrees; i ++) {
		fprintf (stdout, "  %s\n", liste [i] -> d_name);
		free (liste [i]);
	}
	fprintf (stdout, "\n");
	free (liste);

	return (0);
}

