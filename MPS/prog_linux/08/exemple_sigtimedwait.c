	#include <stdio.h>
	#include <stdlib.h>
	#include <signal.h>
	#include <unistd.h>

	int
main (void)
{
	sigset_t         ensemble;
	int              numero;
	struct timespec  delai;
	fprintf (stderr, "PID=%u\n", getpid());
	/* Blocage de tous les signaux */
	sigfillset (& ensemble);
	sigprocmask (SIG_BLOCK, & ensemble, NULL);
	/* Attente de tous les signaux pendant 10 secondes */
	delai . tv_sec = 10;
	delai . tv_nsec = 0;
	sigfillset (& ensemble);
	while (1) {
		if ((numero = sigtimedwait (& ensemble, NULL, & delai)) < 0) {
			perror ("sigtimedwait");
			break;
		}
		fprintf (stderr, "sigtimedwait : %d reçu \n", numero);
	}
	return (0);
}
