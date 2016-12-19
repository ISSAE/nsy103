
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	char * alloc_fgets (FILE * fp);

	int
main (void)
{
	char *	chaine;

	while (1) {
		chaine = alloc_fgets (stdin);
		if (chaine == NULL)
			/* Pas assez de mémoire */
			break;
		if ((chaine [0] == '\n') || (chaine [0] == '\0'))
			/* Chaine vide... on quitte */
			break;
		fprintf (stdout, "%d caractères\n", strlen (chaine));
		free (chaine);
	}
	return (0);
}


	char *
alloc_fgets (FILE * fp)
{
	char *	retour = NULL;
	char *  a_ecrire = NULL;
	int	taille = 64;

	retour = (char *) malloc (taille);
	a_ecrire = retour;

	while (1) {
		if (fgets (a_ecrire, 64, fp) == NULL)
			break;
		if (strlen (a_ecrire) < 63)
			break;
		/* On se place sur le caractère nul final */
		a_ecrire = a_ecrire + 63; 
		/* Et l'on agrandit également le buffer de 63 caractères */
		taille += 63;
		retour = realloc (retour, taille);
		if (retour == NULL)
			break;
	}
	return (retour);
}


