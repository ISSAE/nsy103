
	#include <stdio.h>
	#include <glob.h>

	int
main (int argc, char * argv [])
{
	glob_t	chemins;
	int 	i;
	int	erreur;

	if (argc < 2) {
		fprintf (stderr, "Syntaxe : %s motif...\n", argv [0]);
		exit (1);
	}
	erreur = glob (argv [1], 0, NULL, & chemins);
	if ((erreur != 0) && (erreur != GLOB_NOMATCH))
		perror (argv [1]);
	for (i = 2; i < argc; i ++) {
		erreur = glob (argv [i], GLOB_APPEND, NULL, & chemins);
		if ((erreur != 0) && (erreur != GLOB_NOMATCH))
			perror (argv [i]);
	}
	for (i = 0; i < chemins . gl_pathc; i ++)
		fprintf (stdout, "%s\n", chemins . gl_pathv [i]);
	globfree (& chemins);
	return (0);
}
