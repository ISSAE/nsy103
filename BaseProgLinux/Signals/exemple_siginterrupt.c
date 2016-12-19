

	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <errno.h>

	#include <signal.h>


	void
gestionnaire (int numero)
{
	fprintf (stdout, "\ngestionnaire de signal %d\n", numero); 
}

	int
main (int argc, char * argv [])
{
	int i;

	if ((argc != 2) || (sscanf (argv [1], "%d", & i) != 1)) {
		fprintf (stderr, "Syntaxe : %s {0|1}\n", argv [0]);
		exit (1);
	}
	
	signal (SIGTSTP, gestionnaire);
	siginterrupt (SIGTSTP, i);

	while (1) {
		fprintf (stdout, "appel read()\n");
		if (read (0, &i, sizeof (int)) < 0)
			if (errno == EINTR)
				fprintf (stdout, "EINTR \n");
	}

	return (0);	
}

	
