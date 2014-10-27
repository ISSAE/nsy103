	#include <stdio.h>
	#include <stdlib.h>
	#include <signal.h>
	#include <setjmp.h>
	#include <unistd.h>

	sigjmp_buf	contexte_sigalrm;

	void
gestionnaire_sigalrm (int inutilise)
{
	siglongjmp (contexte_sigalrm, 1);
}

	int
main (void)
{
	char	ligne [80];
	int	i;

	signal (SIGALRM, gestionnaire_sigalrm);

	fprintf (stdout, "Entrez un nombre entier avant 5 secondes : ");

	if (sigsetjmp (contexte_sigalrm, 1) == 0) {
		/* premier passage, installation */
		alarm (5);
	
		/* Lecture et analyse de la ligne saisie */
		while (1) {
			if (fgets (ligne, 79, stdin) != NULL)
				if (sscanf (ligne, "%d", & i) == 1)
					break;
			fprintf (stdout, "Un entier svp : ");
		}

		/* Ok - La ligne est bonne */
		alarm (0);
		fprintf (stdout, "Ok !\n");

	} else {
		/* On est arrivé par SIGALRM */
		fprintf (stdout, "\nTrop tard !\n");
		exit (1);
	}
	return (0);
}

