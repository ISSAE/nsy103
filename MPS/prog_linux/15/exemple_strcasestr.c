
	#define _GNU_SOURCE
	#include <stdio.h>
	#include <string.h>
	#include <locale.h>

	int
main (int argc, char * argv [])
{
	int	i;
	char * 	chaine;

	setlocale (LC_ALL, "");

	if (argc != 3) {
		fprintf (stderr, "Syntaxe : %s chaine sous-chaine\n", argv [0]);
		exit (1);
	}
	if (strlen (argv [2]) == '\0') {
		/* Cela eut arriver si on a lanc� le programme avec
		 * un execv() un peu vicieux...
		 */
		fprintf (stderr, "La sous-chaine recherch�e est vide !\n");
		exit (1);
	}
	i = 0;
	chaine = argv [1];
	while (1) {
		chaine = strcasestr (chaine, argv [2]);
		if (chaine == NULL)
			break;
		/* on saute la sous-chaine trouv�e */
		chaine += strlen (argv [2]);
		i ++;
	}
	if (i == 0)
		fprintf (stdout, "%s ne se trouve pas dans %s\n",
				argv [2], argv [1]);
	else
		fprintf (stdout, "%s a �t� trouv�e %d fois dans %s\n",
				argv [2], i, argv [1]);

	return (0);
}

