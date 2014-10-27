
	#include <stdio.h>

	int
main (void)
{
	int i;

	fprintf (stdout, "Veuillez entrer un entier : ");
	while (1) {
		if (scanf ("%d", & i) == 1)
			break;
		fprintf (stdout, "\nErreur, un entier svp :");
	}
	fprintf (stdout, "\nOk\n");
	return (0);
}
