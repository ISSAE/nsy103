
	#include <stdio.h>
	#include <string.h>

	#define LG_MAXI	32	/* 20 + 12, cf plus bas */

	int
main (int argc, char * argv [])
{
	int	i;
	int	taille;
	char 	chaine [LG_MAXI + 1];

	strcpy (chaine, "Arguments : "); /* déjà 12 caractères */

	for (i = 1; i < argc; i ++) {
		taille = strlen (chaine);
		strncat (chaine, argv [i], LG_MAXI - taille);
	}

	fprintf (stdout, "%s\n", chaine);

	return (0);
}
