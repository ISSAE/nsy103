
	#include <signal.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

	void
gestionnaire (int numero, struct siginfo * info, void * inutilise)
{
	fprintf (stderr, "Recu %d\n", numero);
	fprintf (stderr, "  si_code = %d\n", info -> si_code);
}

	int
main (void)
{
	int              i;
	struct sigaction action;
	char             chaine [5];

	action . sa_sigaction = gestionnaire;
	action . sa_flags = SA_SIGINFO;
	sigemptyset (& action . sa_mask);
	fprintf (stderr, "PID=%u\n", getpid());
	for (i = 1; i < NSIG; i ++)
		if (sigaction (i, & action, NULL) < 0)
			fprintf (stderr, "%d non intercepté\n", i);
	while (1)
		fgets (chaine, 5, stdin);
	return (0);
}
