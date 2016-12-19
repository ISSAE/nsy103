	#include <stdio.h>
	#include <stdlib.h>

	int *
calcul_fibonacci (int nombre_de_valeurs)
{
	int *	table = NULL;
	int	i;

	if ((table = calloc (nombre_de_valeurs, sizeof (int))) == NULL) {
		fprintf (stderr, "Pas assez de m�moire\n");
		exit (1);
	}
	if (nombre_de_valeurs > 0) {
		table [0] = 1;
		if (nombre_de_valeurs > 1) {
			table [1] = 1;
			for (i = 2; i < nombre_de_valeurs; i ++)
				table [i] = table [i - 2] + table [i - 1];
		}
	}
	return (table);
}

	int
main (int argc, char * argv [])
{
	int	nb_valeurs;
	int *	table;
	int	i;

	if ((argc != 2) || (sscanf (argv [1], "%d", & nb_valeurs) != 1)) {
		fprintf (stderr, "Syntaxe : %s nombre_de_valeurs\n", argv [0]);
		exit (1);
	}	
	table = calcul_fibonacci (nb_valeurs);
	for (i = 0; i < nb_valeurs; i ++)
		fprintf (stdout, "%d\n", table [i]);
	free (table);
	return (0);
}
