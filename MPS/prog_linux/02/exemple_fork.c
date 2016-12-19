	#include <stdlib.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <errno.h>
	#include <sys/wait.h>

	int
main (void)
{

	pid_t	pid_fils;


	do {

		pid_fils = fork ();

	} while ((pid_fils == -1) && (errno == EAGAIN));

	if (pid_fils == -1) {

		fprintf (stderr, "fork() impossible, errno=%d\n", errno);
		return (1);
	}

	if (pid_fils == 0) {
 
		/* processus fils */

		fprintf (stdout, "Fils : PID=%d, PPID=%d\n", 
			getpid (), getppid ());
		return (0);

	} else { 

		/* processus père */

		fprintf (stdout, "Pere : PID=%d, PPID=%d, PID fils=%d\n",
			getpid (), getppid (), pid_fils);
		wait (NULL);
		return (0);
	}
}

