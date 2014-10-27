	#define _GNU_SOURCE
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/types.h>

	int
main (int argc, char * argv [])
{
	int 	i;
	pid_t	pid;
	pid_t	sid;

	if (argc == 1) {
		fprintf (stdout, "%u : %u\n", getpid (), getsid (0));
		return (0);
	}
	for (i = 1; i < argc; i ++)
		if (sscanf (argv [i], "%u", & pid) != 1) {
			fprintf (stderr, "PID invalide : %s\n", argv [i]);
		} else {
			sid = getsid (pid);
			if (sid == -1)
				fprintf (stderr, "%u inexistant\n", pid);
			else
				fprintf (stderr, "%u : %u\n", pid, sid);
		}
	return (0);
}
