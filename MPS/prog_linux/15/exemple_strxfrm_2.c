

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <locale.h>

	typedef struct {
		char	*	originale;
		char	*	modifiee;
	} element_t;

	int
compare_elements (const void * objet_1, const void * objet_2)
{	
	element_t * elem_1 = (element_t *) objet_1;
	element_t * elem_2 = (element_t *) objet_2;

	return (strcmp (elem_1 -> modifiee, elem_2 -> modifiee));
}

	void
trie_table_mots (int nb_mots, char * table_mots [])
{
	element_t *	table_elements;
	size_t		taille;
	int		i;

	table_elements = (element_t *) calloc (nb_mots, sizeof (element_t));
	if (table_elements == NULL) {
		perror ("calloc");
		exit (1);
	}
	for (i = 0; i < nb_mots; i ++) {
		table_elements [i] . originale = table_mots [i];
		taille = strxfrm (NULL, table_elements [i] . originale, 0);
		table_elements [i] . modifiee = (char *) malloc (taille + 1);
		if (table_elements [i] . modifiee == NULL) {
			perror ("malloc");
			exit (1);
		}
		strxfrm (table_elements [i] . modifiee,
			 table_elements [i] . originale,
			 taille);
	}
	qsort (table_elements, nb_mots, sizeof (element_t), compare_elements);

	for (i = 0; i < nb_mots; i ++) {
		fprintf (stdout, "%s\n", table_elements [i] . originale);
		free (table_elements [i] . modifiee);
	}
	free (table_elements);
}

	int
main (int argc, char * argv [])
{
	setlocale (LC_ALL, "");

	if (argc < 2) {
		fprintf (stderr, "Syntaxe : %s mots...\n", argv [0]);
		exit (1);
	}


	trie_table_mots (argc - 1, & (argv [1]));
	return (0);
}
