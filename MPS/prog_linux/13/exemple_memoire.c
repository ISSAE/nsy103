
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>


	int
main (int argc, char * argv [])
{
	char 	ligne_ps [80];
	char **	table = NULL;
	int	i;
	int	nb_blocs;
	int	taille_bloc;

	if ((argc != 3) 
	 || (sscanf (argv [1], "%d", & nb_blocs) != 1)
	 || (sscanf (argv [2], "%d", & taille_bloc) != 1)) {
		fprintf (stderr, "Syntaxe : %s Nb_blocs Taille_bloc\n", argv [0]);
		exit (1);
	}

	if ((nb_blocs < 1) || (taille_bloc < 1)) {
		fprintf (stderr, "Valeurs invalides\n");
		exit (1);
	}

	sprintf (ligne_ps, "ps un %u", getpid());

	fprintf (stdout, "Je démarre...\n");
	system (ligne_ps);

	fprintf (stdout, "J'alloue %d blocs de %d octets...", nb_blocs, taille_bloc);
	fflush (stdout);
	
	table = (char **) calloc (nb_blocs, sizeof (char *));
	if (table == NULL) {
		fprintf (stderr, "Echec\n");
		exit (1);
	}

	for (i = 0; i < nb_blocs; i ++) {
		table [i] = (char *) malloc (taille_bloc);
		if (table [i] == NULL) {
			fprintf (stdout, "Echec\n");
			exit (1);
		}
		memset (table [i], 1, taille_bloc);
	}
	fprintf (stdout, "Ok\n");
	system (ligne_ps);

	fprintf (stdout, "Je libère tous les blocs sauf le dernier\n");
	for (i = 0; i < nb_blocs - 1; i ++)
		free (table [i]);
	system (ligne_ps);

	fprintf (stdout, "Je libère le dernier bloc..\n");
	free (table [nb_blocs - 1]);
	system (ligne_ps);

	return (0);
}
