	#include <stdio.h>
	#include <unistd.h>
	#include <sys/types.h>

	int
main (int argc, char * argv [])
{
	fprintf (stdout, "%u : %u\n", getpid (), getpgrp ());
	return (0);
}
