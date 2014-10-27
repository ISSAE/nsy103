
	#include <stdio.h>

	void
fonction_recursive (int iteration)
{
	char * bloc;

	fprintf (stdout, "Iteration %d\n", iteration);
	fflush (stdout);
	if ((bloc = alloca (512 * 1024)) == NULL) {
		fprintf (stdout, "Echec\n");
		return;
	}
	fonction_recursive (iteration + 1);
}

	int
main (void)
{
	fonction_recursive (1);
	return (0);
}
