
	#include <stdio.h>

	int
main (void)
{
	int i, j, k;

	if (fscanf (stdin, "i = %d j = %d k = %d", & i, & j, & k) == 3)
		fprintf (stdout, "Ok (%d, %d, %d)\n", i, j, k);
	else
		fprintf (stdout, "Erreur\n");

	return (0);
}
