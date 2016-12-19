	#include <stdio.h>
	#include <time.h>
	#include <unistd.h>
	#include <sys/time.h>

	int
main (void)
{
	struct timeval  timev;

	if (gettimeofday (& timev, NULL) != 0) {
		perror ("gettimeofday");
		exit (1);
	}
	fprintf (stdout, "time() : %ld\n", time (NULL));
	fprintf (stdout, "gettimeofday() : %ld.%06ld\n",
		timev . tv_sec, timev . tv_usec);
	return (0);
}

