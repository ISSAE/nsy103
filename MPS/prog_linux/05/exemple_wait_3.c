
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <signal.h>
	#include <errno.h>
	#include <sys/wait.h>
	#include <sys/resource.h>


	int
main (void)
{
	pid_t	pid;
	int	status;
	struct rusage usage;
	int	i, j;

	switch ( pid = fork ()) {
		case -1 :
			fprintf (stderr, "Erreur dans fork()\n");
			exit (1);
		case 0 : /* fils */
			fprintf (stdout, "Fils : PID = %u\n", getpid ());
			j = 0;
			for (i = 0; i < 5000000; i ++)
				j += i;
			raise (SIGSTOP);
			for (i = 0; i < 500000; i ++) {
				FILE * fp;
				fp = fopen ("exemple_wait_2", "r");
				if (fp != NULL)
					fclose (fp);
			}
			exit (0);	
				
		default : /* père */
			break;
	}

	while (1) {
		sleep (1);
		if ((pid=wait3 (& status, WUNTRACED | WNOHANG, & usage)) > 0) {
			if (WIFEXITED (status)) {
				fprintf (stdout, "%u terminé par exit (%d)\n",
						pid, WEXITSTATUS (status));
			} else if (WIFSIGNALED (status)) {
				fprintf (stdout, "%u terminé par signal %d\n",
						pid, WTERMSIG (status));
			} else if (WIFSTOPPED (status)) {
				fprintf (stdout, "%u stoppé par signal %d\n",
						pid, WSTOPSIG (status));
				fprintf (stdout, "Je le relance\n");
				kill (pid, SIGCONT);
			}
			fprintf (stdout, "Temps utilisateur %ld s, %ld µs\n",
					usage . ru_utime . tv_sec,
					usage . ru_utime . tv_usec);
			fprintf (stdout, "Temps en mode noyau %ld s, %ld µs\n",
					usage . ru_stime . tv_sec,
					usage . ru_stime . tv_usec);
		} else if (errno == ECHILD) {
			/* Plus de fils */
			break;
		} 
	}
	return (EXIT_SUCCESS);
}

