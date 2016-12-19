
	#define _GNU_SOURCE
	#include <stdio.h>
	#include <string.h>

	int
main (int argc, char * argv[])
{
	char * chaine;

	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s chaine\n", argv [0]);
		exit (1);
	}

	chaine = strdup (argv [1]);
	strfry (chaine);
	fprintf (stdout, "%s\n", chaine);
			
	return (0);
}
