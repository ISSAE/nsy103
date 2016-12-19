
	#include <stdio.h>
	#include <stdlib.h>
	#include <mcheck.h>

	int
main (void)
{
	char * ptr;

	mtrace();

	if ((ptr = (char *) malloc (512)) == NULL) {
		perror ("malloc");
		exit (1);
	}
	free (ptr);

	return (0);
}
