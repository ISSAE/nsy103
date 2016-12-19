
	#include <stdio.h>
	#include <errno.h>

	int
main (void)
{
	int i;
	for (i = 0; i < sys_nerr; i++)
		if (sys_errlist [i] != NULL)
			fprintf (stdout, "%d : %s\n", i, sys_errlist [i]);
		else
			fprintf (stdout, "** Pas de message pour %d **\n", i);
	return (0);
}
