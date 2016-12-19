
	#include <stdio.h>
	#include <stdlib.h>
	#include <signal.h>
	#include <errno.h>

	int
main (void)
{
	int i;
	struct sigaction action;
	for (i = 1; i < NSIG; i ++) {
		if (sigaction (i, NULL, & action) != 0)
			fprintf (stderr, "Erreur sigaction %d\n", errno);
		if (action . sa_handler != SIG_DFL) {
			fprintf (stdout, "%d (%s) comportement ",
				i, sys_siglist [i]);
			if (action . sa_handler == SIG_IGN)
				fprintf (stdout, ": ignorer\n");
			else
				fprintf (stdout, "personnalisé\n");
		}
	}
	return (0);
}
