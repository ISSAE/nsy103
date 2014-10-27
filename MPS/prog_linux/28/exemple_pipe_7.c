
	#include <stdio.h>
	#include <unistd.h>


	int
main (void)
{
	int	tube [2];
	char	c = 'c';
	int	i;

	fprintf (stdout, "Création tube\n");
	if (pipe (tube) != 0) {
		perror ("pipe");
		exit (1);
	}
	fprintf (stdout, "Écriture dans tube\n");
	for (i = 0; ; i ++) {
		fprintf (stdout, "%d octets écrits\n", i);
		if (write (tube [1], & c, 1) != 1) {
			perror ("write");
			exit (1);
		}
	}
	return (0);
}
