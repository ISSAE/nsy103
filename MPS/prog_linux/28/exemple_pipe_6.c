	#include <signal.h>
	#include <stdio.h>
	#include <unistd.h>

	int
main (void)
{
	int	tube [2];
	char *	buffer = "AZERTYUIOP";

	signal (SIGPIPE, SIG_IGN);

	fprintf (stdout, "Création tube\n");
	if (pipe (tube) != 0) {
		perror ("pipe");
		exit (1);
	}
	fprintf (stdout, "Fermeture sortie\n");
	close (tube [0]);
	fprintf (stdout, "Écriture dans tube\n");
	if (write (tube [1], buffer, strlen (buffer)) != strlen (buffer)) {
		perror ("write");
		exit (1);
	}
	fprintf (stdout, "Fin du programme\n");
	return (0);
}
