
	#include <stdio.h>
	#include <stdlib.h>

	int
main (int argc, char * argv [])
{

	if (argc != 3) {
		fprintf (stderr, "Syntaxe : %s arg1 arg2\n", argv [0]);
		exit (1);
	}
	fprintf (stdout, "strcmp (%s, %s) = %d\n", argv [1], argv [2],
			strcmp (argv [1], argv [2]));
	return (0);
}
