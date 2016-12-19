
	#include <stdio.h>
	#include <stdlib.h>
	#include <mcheck.h>

	void	fonction_d_erreur (enum mcheck_status status);

	#define NB_INT	20

	int
main (void)
{
	int * table_int;
	int	i;

	if (mcheck (fonction_d_erreur) != 0) {
		perror ("mcheck");
		exit (1);
	}
	fprintf (stdout, "Allocation de la table\n");	
	table_int = calloc (NB_INT, sizeof (int));

	fprintf (stdout, "On déborde vers le haut\n");
	for (i = 0; i <= NB_INT; i ++)
		table_int [i] = 1;
	
	fprintf (stdout, "Libération de la table\n");
	free (table_int);

	fprintf (stdout, "Allocation de la table\n");	
	table_int = calloc (NB_INT, sizeof (int));

	fprintf (stdout, "On déborde vers le bas\n");
	i = NB_INT;
	while (i >= 0)
		table_int [--i] = 1;
	
	fprintf (stdout, "Libération de la table\n");
	free (table_int);

	fprintf (stdout, "Allocation de la table\n");	
	table_int = calloc (NB_INT, sizeof (int));

	fprintf (stdout, "Ecriture normale\n");
	for (i = 0; i < NB_INT; i ++)
		table_int [i] = 0;

	fprintf (stdout, "Libération de la table\n");
	free (table_int);

	fprintf (stdout, "Et re-libération de la table !\n");
	free (table_int);

	return (0);
}

	void
fonction_d_erreur (enum mcheck_status status)
{
	switch (status) {
		case MCHECK_DISABLED :
			fprintf (stdout, " -> Pas de vérification\n");
			break;
		case MCHECK_OK :
			fprintf (stdout, " -> Vérification Ok\n");
			break;
		case MCHECK_HEAD :
			fprintf (stdout, " -> Données avant un bloc écrasées\n");
			break;
		case MCHECK_TAIL :
			fprintf (stdout, " -> Données après un bloc écrasées\n");
			break;
		case MCHECK_FREE :
			fprintf (stdout, " -> Bloc déjà libéré\n");
			break;
	}
}

