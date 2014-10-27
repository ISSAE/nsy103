
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <errno.h>

	int
main (void)
{
	char * argv [] = { "ls", "-l", "-n", NULL };

	execvp ("ls", argv);

	fprintf (stderr, "Erreur %d\n", errno);
	return (1);
}
