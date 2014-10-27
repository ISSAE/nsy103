
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

	int
main (void)
{
	pid_t pid;

	fprintf (stdout, "Père : mon PID est %u\n", getpid());
	
	if ((pid = fork()) < 0) {
		fprintf (stderr, "echec fork()\n");
		exit (1);
	}


	if (pid != 0) {
		/* processus père */
		sleep (2);
		fprintf (stdout, "Père : je me termine\n");
		exit (0);
	} else {
		/* processus fils */

		fprintf (stdout, "Fils : mon père est %u\n", getppid ());
		sleep (1);
		fprintf (stdout, "Fils : mon père est %u\n", getppid ());
		sleep (1);
		fprintf (stdout, "Fils : mon père est %u\n", getppid ());
		sleep (1);
		fprintf (stdout, "Fils : mon père est %u\n", getppid ());
		sleep (1);
		fprintf (stdout, "Fils : mon père est %u\n", getppid ());
	}
	return (0);
}	
