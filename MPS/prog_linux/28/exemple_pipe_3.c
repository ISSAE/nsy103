	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>


	int
main (int argc, char * argv [])
{
	int	tube [2];

	if (argc != 3) {
		fprintf (stderr, "Syntaxe : %s commande_1 commande_2\n",
				argv [0]);
		exit (1);
	}

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
			close (tube [0]);
			dup2 (tube [1], STDOUT_FILENO);
			system (argv [1]);
			break;
		default :
			close (tube [1]);
			dup2 (tube [0], STDIN_FILENO);
			system (argv [2]);
			break;
	}
	return (0);
}
