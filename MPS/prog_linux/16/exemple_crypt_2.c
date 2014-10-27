	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include <crypt.h>

	int
main (int argc, char * argv [])
{
	char *	cryptage;

	if (argc != 3) {
		fprintf (stderr, "Syntaxe : %s mot_passe bouillie\n", argv[0]);
		exit (1);
	}

	cryptage = crypt (argv [1], argv [2]);
	if (strcasecmp (cryptage, argv [2]) == 0)
		fprintf (stdout, "Vérification Ok\n");
	else
		fprintf (stdout, "Mauvais mot de passe\n");
	exit (0);
}
