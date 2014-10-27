
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/wait.h>


	int
main (void)
{
	int		tube [2];
	unsigned char	buffer [256];
	int		i;

	fprintf (stdout, "Création tube\n");
	if (pipe (tube) != 0) {
		perror ("pipe");
		exit (1);
	}
	switch (fork ()) {
		case -1 :
			perror ("fork()");
			exit (1);
			break;
		case 0 :
			fprintf (stdout, "Fils : Fermeture entrée\n");
			close (tube [1]);
			fprintf (stdout, "Fils : Lecture tube\n");
			if (read (tube [0], buffer, 256) != 256) {
				perror ("read");
				exit (1);
			}
			fprintf (stdout, "Fils : Vérification \n");
			for (i = 0; i < 256; i ++)
				if (buffer [i] != i) {
					fprintf (stdout, "Fils : Erreur\n");
					exit (1);
				}
			fprintf (stdout, "Fils : Ok\n");
			break;
		default :
			fprintf (stdout, "Père : Fermeture sortie\n");
			close (tube [0]);
			for (i = 0; i < 256; i ++)
				buffer [i] = i;
			fprintf (stdout, "Père : Écriture dans tube\n");
			if (write (tube [1], buffer, 256) != 256) {
				perror ("write");
				exit (1);
			}
			wait (NULL);
			break;
	}
	return (0);
}
