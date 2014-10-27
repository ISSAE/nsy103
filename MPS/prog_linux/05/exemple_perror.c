	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/resource.h>
	#include <sys/wait.h>

	int
main (void)
{
	struct rlimit limite;
	pid_t	pid;

	if (getrlimit (RLIMIT_NPROC, & limite) != 0) {
		perror ("getrlimit");
		exit (1);
	}
	limite . rlim_cur = 16;
	if (setrlimit (RLIMIT_NPROC, & limite) != 0) {
		perror ("setrlimit");
		exit (1);
	}
	while (1) {
		pid = fork ();
		if (pid == (pid_t) -1) {
			perror ("fork");
			exit (1);
		}
		if (pid != 0) {
			fprintf (stdout, "%u\n", pid);
			fflush (stdout);
			if (waitpid (pid, NULL, 0) != pid)
				perror ("waitpid");
			return (0);
		}
	}
	return (0);
}
