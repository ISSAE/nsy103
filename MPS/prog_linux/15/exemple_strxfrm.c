
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <locale.h>

	int
main (int argc, char * argv [])
{
	char *	chaine_1 = NULL;
	char *  chaine_2 = NULL;
	size_t	taille_1;
	size_t	taille_2;
	int	compar;

	setlocale (LC_ALL, "");

	if (argc != 3) {
		fprintf (stderr, "Syntaxe : %s chaine_1 chaine_2\n", argv [0]);
		exit (1);
	}

	taille_1 = strxfrm (NULL, argv [1], 0);
	taille_2 = strxfrm (NULL, argv [2], 0);

	if (((chaine_1 = (char *) malloc (taille_1 + 1)) == NULL)
	 || ((chaine_2 = (char *) malloc (taille_2 + 1)) == NULL)) {
		perror ("malloc");
		exit (1);
	}

	strxfrm (chaine_1, argv [1], taille_1);
	strxfrm (chaine_2, argv [2], taille_2);


	compar = strcmp (chaine_1, chaine_2);
	fprintf (stdout, "strxfrm / strcmp : %s %c %s\n", argv [1],
		(compar == 0 ? '=' : (compar < 0 ? '<' : '>')), argv [2]);

	compar = strcoll (argv [1], argv [2]);
	fprintf (stdout, "strcoll : %s %c %s\n", argv [1],
		(compar == 0 ? '=' : (compar < 0 ? '<' : '>')), argv [2]);

	return (0);
}

