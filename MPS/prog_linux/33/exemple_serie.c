	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <stdio.h>
	#include <unistd.h>

	int
main (int argc, char * argv [])
{
	int 	fd;
	char	chaine [2];

	if (argc != 2) {
		fprintf (stderr, "%s <fichier sp�cial>\n", argv [0]);
		exit (1);
	}

	fprintf (stdout, "Nous allons v�rifier la tension entre les broches :\n"
			 "  7 (-) et 20 (+) pour un connecteur DB-25 \n"
			 "  5 (-) et  4 (+) pour un connecteur DB-9 \n \n ");

	fprintf (stdout, "La tension doit �tre inf�rieure � -3 V \n");
	fprintf (stdout, "Pressez Entr�e pour continuer\n");
	fgets (chaine, 2, stdin);

	fd = open (argv [1], O_RDONLY | O_NONBLOCK);
	if (fd < 0) {
		perror ("open");
		return (1);
	}
	fprintf (stdout, "La tension doit �tre sup�rieur � +3 V\n");
	fprintf (stdout, "Pressez Entr�e pour continuer\n");
	fgets (chaine, 2, stdin);

	
	fprintf (stdout, "La tension doit �tre � nouveau < -3 V\n");
	if (close (fd) < 0) {
		perror ("close");
		return (1);
	}
	return (0);
}

