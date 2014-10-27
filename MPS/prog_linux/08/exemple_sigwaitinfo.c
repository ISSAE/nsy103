	#include <stdio.h>
	#include <stdlib.h>
	#include <signal.h>
	#include <unistd.h>

	void
gestionnaire (int numero, struct siginfo * info, void * inutile)
{
	fprintf (stderr, "gestionnaire : %d reçu \n", numero);
}

	int
main (void)
{
	sigset_t         ensemble;
	int              numero;
	struct sigaction action;
	fprintf (stderr, "PID=%u\n", getpid());
	/* Installation gestionnaire pour SIGRTMIN+1 */
	action . sa_sigaction = gestionnaire;
	action . sa_flags = SA_SIGINFO;
	sigemptyset (& action. sa_mask);
	sigaction (SIGRTMIN + 1, & action, NULL);
	/* Blocage de tous les signaux sauf SIGRTMIN+1 */
	sigfillset (& ensemble);
	sigdelset (& ensemble, SIGRTMIN + 1);
	sigprocmask (SIG_BLOCK, & ensemble, NULL);
	/* Attente de tous les signaux sauf RTMIN+1 et SIGKILL */
	sigfillset (& ensemble);
	sigdelset (& ensemble, SIGRTMIN + 1);
	sigdelset (& ensemble, SIGKILL);
	while (1) {
		if ((numero = sigwaitinfo (& ensemble, NULL)) < 0)
			perror ("sigwaitinfo");
		else
			fprintf (stderr, "sigwaitinfo : %d reçu\n", numero);
	}
	return (0);
}
