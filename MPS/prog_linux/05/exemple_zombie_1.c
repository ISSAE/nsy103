
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

	int
main (void)
{
	pid_t pid;
	char  commande [128];

	if ((pid = fork()) < 0) {
		fprintf (stderr, "echec fork()\n");
		exit (1);
	}

	if (pid == 0) {
		/* processus fils */
		sleep (2);
		fprintf (stdout, "Le processus fils %u se termine\n", getpid());
		exit (0);
	} else {
		/* processus père */

		sprintf (commande, "ps %u", pid);
		system (commande);
		sleep (1);
		system (commande);
		sleep (1);
		system (commande);
		sleep (1);
		system (commande);
		sleep (1);
		system (commande);
		sleep (1);
		system (commande);
	}
	return (0);
}	
