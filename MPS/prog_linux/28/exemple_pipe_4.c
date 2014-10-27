	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/stat.h>


	int
invoque_processus (const char * commande, int fd [2])
{
	int	tube_1 [2];
	int	tube_2 [2];
	if ((pipe (tube_1) != 0) || (pipe (tube_2) != 0))
		return (-1);
	switch (fork ()) {
		case -1 :
			close (tube_1 [0]); close (tube_1 [1]);
			close (tube_2 [0]); close (tube_2 [1]);
			return (-1);
		case 0 : 
			close (tube_1 [1]);
			close (tube_2 [0]);
			dup2 (tube_1 [0], STDIN_FILENO);
			dup2 (tube_2 [1], STDOUT_FILENO);
			system (commande);
			exit (0);
		default :
			close (tube_1 [0]);
			close (tube_2 [1]);
			fd [0] = tube_2 [0];
			fd [1] = tube_1 [1];
	}
	return (0);
}


	int
main (int argc, char * argv [])
{
	int	tube [2];
	FILE *	fichier;
	char *	contenu;
	struct stat status;
	char	c;

	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s fichier\n", argv [0]);
		exit (1);
	}
	if (stat (argv [1], & status) != 0) {
		perror ("stat");
		exit (1);
	}
	if ((contenu = malloc (status . st_size)) == NULL) {
		perror ("malloc");
		exit (1);
	}
	if ((fichier = fopen (argv [1], "r")) == NULL) {
		perror ("fopen");
		exit (1);
	}
	if (fread (contenu, 1, status . st_size, fichier) != status . st_size) {
		perror ("fread");
		exit (1);
	}
	fclose (fichier);

	if (invoque_processus ("wc -w", tube) != 0) {
		perror ("invoque_processus");
		exit (1);
	}
	write (tube [1], contenu, status . st_size);
	close (tube [1]);

	fprintf (stdout, "Nombre de mots :   ");
	while (read (tube [0], & c, 1) == 1)
		fputc (c, stdout);
	close (tube [0]);

	if (invoque_processus ("wc -l", tube) != 0) {
		perror ("invoque_processus");
		exit (1);
	}
	write (tube [1], contenu, status . st_size);
	close (tube [1]);

	fprintf (stdout, "Nombre de lignes : ");
	while (read (tube [0], & c, 1) == 1)
		fputc (c, stdout);
	close (tube [0]);

	free (contenu);
	return (0);
}
