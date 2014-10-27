
	#include <stdio.h>
	#include <stdlib.h>
	#include <signal.h>
	#include <time.h>
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
	struct timespec  spec;
	int		 i;

	if ((pid = fork()) < 0) {
		fprintf (stderr, "Erreur dans fork\n");
		exit (1);
	}

	action . sa_handler = gestionnaire_sigusr1;
	sigemptyset (& (action . sa_mask));
	action . sa_flags = SA_RESTART;

	if (sigaction (SIGUSR1, & action, NULL) != 0) {
		fprintf (stderr, "Erreur dans sigaction\n");
		exit (1);
	}

	if (pid == 0) {
		spec . tv_sec = 60;
		spec . tv_nsec = 0;
		system ("date +\"%H:%M:%S\"");
		while (nanosleep (& spec, & spec) != 0)
			;
		system ("date +\"%H:%M:%S\"");
	
	} else {
		sleep (2); /* Pour éviter d'envoyer un signal pendant */
			   /* l'appel system() à /bin/date            */
		for (i = 0 ; i < 59; i ++) {
			sleep (1);
			kill (pid, SIGUSR1);
			kill (pid, SIGUSR1);
			kill (pid, SIGUSR1);
			kill (pid, SIGUSR1);
			kill (pid, SIGUSR1);
		}
		waitpid (pid, NULL, 0);
	}

	return (0);
}

