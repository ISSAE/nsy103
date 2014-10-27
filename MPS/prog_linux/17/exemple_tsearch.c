
	#include <search.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	int
compare_char (const void * lm1, const void * lm2)
{
	return (strcmp (lm1, lm2));
}

	static	VISIT	type_parcours;

	void
parcours (const void * noeud, const VISIT methode, const int profondeur)
{
	if (methode == type_parcours)
		fprintf (stdout, "%s ", * (char **) noeud);
	else if (methode == leaf)
		fprintf (stdout, "(%s) ", * (char **) noeud);
}

	int
main (void)
{
	int	i;
	void *	racine = NULL;
	char *	chaines [] = {
	"A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P",
	"Q", "S", "D", "F", "G", "H", "J", "K", "L", "M",
	"W", "X", "C", "V", "B", "N", NULL,
	};

	/* Insertion des chaines dans l'arbre binaire */

	for (i = 0; chaines [i] != NULL; i ++)
		if (tsearch (chaines [i], & racine, compare_char) == NULL) {
			perror ("tsearch");
			exit (1);
		}

	for (i = 0; chaines [i] != NULL; i ++)
		if (tfind (chaines [i], & racine, compare_char) == NULL) {
			fprintf (stderr, "%s perdue ?\n", chaines [i]);
			exit (1);
	}

	fprintf (stdout, "Parcours preorder (+ leaf) : \n  ");
	type_parcours = preorder;
	twalk (racine, parcours);
	fprintf (stdout, "\n");

	fprintf (stdout, "Parcours postorder (+ leaf) : \n  ");
	type_parcours = postorder;
	twalk (racine, parcours);
	fprintf (stdout, "\n");

	fprintf (stdout, "Parcours endorder (+ leaf) : \n  ");
	type_parcours = endorder;
	twalk (racine, parcours);
	fprintf (stdout, "\n");

	fprintf (stdout, "Parcours leaf : \n  ");
	type_parcours = leaf;
	twalk (racine, parcours);
	fprintf (stdout, "\n");

	return (0);
}
