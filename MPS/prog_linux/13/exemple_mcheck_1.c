
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

	fprintf (stdout, "On d�borde vers le haut\n");
	for (i = 0; i <= NB_INT; i ++)
		table_int [i] = 1;
	
	fprintf (stdout, "Lib�ration de la table\n");
	free (table_int);

	fprintf (stdout, "Allocation de la table\n");	
	table_int = calloc (NB_INT, sizeof (int));

	fprintf (stdout, "On d�borde vers le bas\n");
	i = NB_INT;
	while (i >= 0)
		table_int [--i] = 1;
	
	fprintf (stdout, "Lib�ration de la table\n");
	free (table_int);

	fprintf (stdout, "Allocation de la table\n");	
	table_int = calloc (NB_INT, sizeof (int));

	fprintf (stdout, "Ecriture normale\n");
	for (i = 0; i < NB_INT; i ++)
		table_int [i] = 0;

	fprintf (stdout, "Lib�ration de la table\n");
	free (table_int);

	fprintf (stdout, "Et re-lib�ration de la table !\n");
	free (table_int);

	return (0);
}

	void
fonction_d_erreur (enum mcheck_status status)
{
	switch (status) {
		case MCHECK_DISABLED :
			fprintf (stdout, " -> Pas de v�rification\n");
			break;
		case MCHECK_OK :
			fprintf (stdout, " -> V�rification Ok\n");
			break;
		case MCHECK_HEAD :
			fprintf (stdout, " -> Donn�es avant un bloc �cras�es\n");
			break;
		case MCHECK_TAIL :
			fprintf (stdout, " -> Donn�es apr�s un bloc �cras�es\n");
			break;
		case MCHECK_FREE :
			fprintf (stdout, " -> Bloc d�j� lib�r�\n");
			break;
	}
}

