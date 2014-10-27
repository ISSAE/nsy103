
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
	unsigned int	 duree;
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
		duree = sleep (10);
		system ("date +\"%H:%M:%S\"");
		fprintf (stdout, "Durée restante %u\n", duree);
	
	} else {

		sleep (2);
		kill (pid, SIGUSR1);
		waitpid (pid, NULL, 0);
	}

	return (0);
}

