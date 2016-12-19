
	#include <stdio.h>
	#include <stdlib.h>
	#include <signal.h>
	#include <unistd.h>
	#include <sys/wait.h>

	void
gestionnaire_sigusr1 (int numero)
{
}

	int
main (void)
{
	pid_t 		 pid;
	struct sigaction action; 

	if ((pid = fork()) < 0) {
		fprintf (stderr, "Erreur dans fork\n");
		exit (1);
	}

	action . sa_handler = gestionnaire_sigusr1;
	sigemptyset (& action . sa_mask);
	action . sa_flags = SA_RESTART;

	if (sigaction (SIGUSR1, & action, NULL) != 0) {
		fprintf (stderr, "Erreur dans sigaction\n");
		exit (1);
	}

	if (pid == 0) {

		system ("date +\"%H:%M:%S\"");
		usleep (10000000); /* 10 millions de µs = 10 secondes */
		system ("date +\"%H:%M:%S\"");
	
	} else {

		usleep (2000000); /* 2 millions de µs = 2 secondes */
		kill (pid, SIGUSR1);
		waitpid (pid, NULL, 0);
	}

	return (0);
}

