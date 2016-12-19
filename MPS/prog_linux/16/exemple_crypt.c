	#include <stdio.h>
	#include <unistd.h>
	#include <crypt.h>

	int
main (int argc, char * argv [])
{
	if (argc != 3) {
		fprintf (stderr, "Syntaxe : %s mot_passe prefixe\n", argv[0]);
		exit (1);
	}
	fprintf (stdout, "%s\n", crypt (argv [1], argv [2]));
	exit (0);
}
