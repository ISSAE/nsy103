
	#include <stdio.h>
	#include <stdlib.h>
	#include <signal.h>
	#include <errno.h>
	#include <unistd.h>


#ifdef _POSIX_REALTIME_SIGNALS
	#define NB_SIG_CLASSIQUES	SIGRTMIN
#else
	#define NB_SIG_CLASSIQUES	SIGRTMIN
#endif

	void
gestionnaire (int numero)
{
	fprintf (stdout, "%d (%s) reçu\n", numero, sys_siglist [numero]);
}

	int
main (void)
{
	int i;
	struct sigaction action;
	sigset_t ensemble;

	action . sa_handler = gestionnaire;
	sigemptyset (& (action . sa_mask));
	action . sa_flags = 0; /* Pas de SA_RESTART */
	for (i = 1; i < NSIG; i ++)
		if (sigaction (i, & action, NULL) != 0)
			fprintf (stderr, "%u : %d pas capturé\n",
					getpid(), i);

	/* On bloque tout sauf SIGINT */
	sigfillset (& ensemble);
	sigdelset (& ensemble, SIGINT);
	sigprocmask (SIG_BLOCK, & ensemble, NULL);

	/* un appel système lent bloqué */
	read (0, & i, sizeof (int));
	
	/* Voyons maintenant qui est en attente */
	sigpending (& ensemble);
	for (i = 1; i < NB_SIG_CLASSIQUES; i ++)
		if (sigismember (& ensemble, i))
			fprintf (stdout, "en attente %d (%s)\n", 
				i, sys_siglist [i]);

	/* On débloque tous les signaux pour les voir arriver */
	sigemptyset (& ensemble);
	sigprocmask (SIG_SETMASK, & ensemble, NULL);
	
	return (0);
}
