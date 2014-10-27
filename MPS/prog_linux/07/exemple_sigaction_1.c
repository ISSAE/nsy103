
	#include <signal.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <errno.h>

	void
gestionnaire (int numero)
{
	switch (numero) {
		case SIGQUIT :
			fprintf (stdout, "\nSIGQUIT reçu\n"); fflush (stdout);
			break;
		case SIGINT :
			fprintf (stdout, "\nSIGINT reçu\n"); fflush (stdout);
			break;
	}
}

	int
main (void)
{
	struct sigaction action;

	action . sa_handler = gestionnaire;
	sigemptyset (& (action . sa_mask));
	action . sa_flags = 0;

	if (sigaction (SIGQUIT, & action, NULL) != 0) {
		fprintf (stderr, "Erreur %d\n", errno);
		exit (1);
	}

	action . sa_handler = gestionnaire;
	sigemptyset (& (action . sa_mask));
	action . sa_flags = SA_RESTART | SA_RESETHAND;

	if (sigaction (SIGINT, & action, NULL) != 0) {
		fprintf (stderr, "Erreur %d\n", errno);
		exit (1);
	}

	/* Lecture continue, pour avoir un appel-système lent  bloqué */
	while (1) {
		int i;
		fprintf (stdout, "appel read()\n");
		if (read (0, &i, sizeof (int)) < 0)
			if (errno == EINTR)
				fprintf (stdout, "EINTR \n");
	}
	return (0);

}

