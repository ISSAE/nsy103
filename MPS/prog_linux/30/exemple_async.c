	#define _GNU_SOURCE
	#include <fcntl.h>
	#include <signal.h>
	#include <stdio.h>
	#include <unistd.h>

	void
gestionnaire (int signum, siginfo_t * info, void * vide)
{
	char ligne [256];
	int  lg;
	if (info -> si_code == SI_SIGIO)
		if ((lg = read (info -> si_fd, ligne, 256)) > 0) {
			ligne [lg] = '\0'; 
			fprintf (stdout, "Lu : %s", ligne);
		}
}

	int
main (void)
{
	struct sigaction action;

	action . sa_sigaction = gestionnaire;
	action . sa_flags     = SA_SIGINFO;
	sigemptyset (& action . sa_mask);
	if (sigaction (SIGRTMIN + 5, & action, NULL) < 0) {
		perror ("sigaction");
		exit (1);
	}

	if (fcntl (STDIN_FILENO, F_SETOWN, getpid()) < 0) {
		perror ("fcntl (SETOWN)");
		exit (1);
	}
	if (fcntl (STDIN_FILENO, F_SETSIG, SIGRTMIN + 5) < 0) {
		perror ("fcntl (SETSIG)");
		exit (1);
	}
	if (fcntl (STDIN_FILENO, F_SETFL, fcntl (STDIN_FILENO, F_GETFL) | O_ASYNC) < 0) {
		perror ("fcntl");
		exit (1);
	}
	while (1) {
		fprintf (stdout, "\n Entrez une chaîne SVP :");
		fflush (stdout);
		sleep (5);
	}
	return (0);
}
