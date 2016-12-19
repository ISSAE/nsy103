
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <signal.h>
	#include <sys/wait.h>


	int
main (void)
{
	pid_t	pid;
	int	status;

	switch ( pid = fork ()) {
		case -1 :
			fprintf (stderr, "Erreur dans fork()\n");
			exit (1);
		case 0 : /* fils 1 */
			fprintf (stdout, "Fils 1 : PID = %u\n", getpid ());
			while (1)
				pause ();
		default : /* père */
			break;
	}

	/* Créons un fils que l'on n'attend pas */
	switch (fork ()) {
		case -1 :
			fprintf (stderr, "Erreur dans fork()\n");
			exit (1);
		case 0 : /* fils 2 */
			fprintf (stdout, "Fils 2 : PID = %u\n", getpid ());
			sleep (2);	
			exit (0);
		default : /* père */
			break;
	}
	while (1) {
		sleep (1);
		if (waitpid (pid, & status, WUNTRACED | WNOHANG) > 0) {
			if (WIFEXITED (status)) {
				fprintf (stdout, "%u terminé par exit (%d)\n",
						pid, WEXITSTATUS (status));
				exit (EXIT_SUCCESS);
			} else if (WIFSIGNALED (status)) {
				fprintf (stdout, "%u terminé par signal %d\n",
						pid, WTERMSIG (status));
				exit (EXIT_SUCCESS);
			} else if (WIFSTOPPED (status)) {
				fprintf (stdout, "%u stoppé par signal %d\n",
						pid, WSTOPSIG (status));
			}
		} 
	}
	return (EXIT_SUCCESS);
}

