	#include <signal.h>
	#include <stdio.h>
	#include <stdlib.h>

	void
gestionnaire (int inutilise)
{
}

	int
main (void)
{
	struct sigaction action;

	signal (SIGUSR1, gestionnaire);

	sigaction (SIGUSR1, NULL, & action);
	if (action . sa_handler == gestionnaire)
		fprintf (stdout, "Même adresse\n");
	else
		fprintf (stdout, "Adresse différente\n");

	return (0);
}
