
	#define _GNU_SOURCE

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>


	int
main (void)
{
	char *	chaine;
	size_t	taille;
	ssize_t	retour;

	while (1) {
		taille = 0;
		chaine = NULL;
	
		retour = getline (& chaine, & taille, stdin);	
		if (retour == -1)
			break;
		fprintf (stdout, "%d caract�res lus\n", retour);
		fprintf (stdout, "%d caract�res allou�es\n", taille);
		free (chaine);
	}
	return (0);
}

