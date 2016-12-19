
	#include <stdio.h>
	#include <stdlib.h>


	#define NB_CHAR	20

	int
main (void)
{
	char * table;
	int	i;

	fprintf (stdout, "Allocation de la table\n");	
	table = malloc (NB_CHAR);

	fprintf (stdout, "On déborde vers le haut\n");
	for (i = 0; i <= NB_CHAR; i ++)
		table [i] = 1;
	
	fprintf (stdout, "Libération de la table\n");
	free (table);

	fprintf (stdout, "Allocation de la table\n");	
	table = malloc (NB_CHAR);

	fprintf (stdout, "On déborde vers le bas\n");
	i = NB_CHAR;
	while (i >= 0)
		table [--i] = 1;
	
	fprintf (stdout, "Libération de la table\n");
	free (table);

	fprintf (stdout, "Allocation de la table\n");	
	table = malloc (NB_CHAR);

	fprintf (stdout, "Ecriture normale\n");
	for (i = 0; i < NB_CHAR; i ++)
		table [i] = 0;

	fprintf (stdout, "Libération de la table\n");
	free (table);

	fprintf (stdout, "Et re-libération de la table !\n");
	free (table);

	return (0);
}

