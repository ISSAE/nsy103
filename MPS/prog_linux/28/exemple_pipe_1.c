
	#include <stdio.h>
	#include <unistd.h>


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
	for (i = 0; i < 256; i ++)
		buffer [i] = i;
	fprintf (stdout, "Écriture dans tube\n");
	if (write (tube [1], buffer, 256) != 256) {
		perror ("write");
		exit (1);
	}
	fprintf (stdout, "Lecture depuis tube\n");
	if (read (tube [0], buffer, 256) != 256) {
		perror ("read");
		exit (1);
	}
	fprintf (stdout, "Vérification...");
	for (i = 0; i < 256; i ++)
		if (buffer [i] != i) {
			fprintf (stdout, "Erreur : i=%d buffer [i]=%d\n",
				i, buffer [i]);
			exit (1);
		}
	fprintf (stdout, "Ok\n");
	return (0);
}
