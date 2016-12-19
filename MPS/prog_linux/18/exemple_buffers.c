
	#include <stdio.h>

	int
main (void)
{
	char chaine [10];

	fprintf (stdout, "1 stdout : ligne + \\n\n");
	fprintf (stdout, "2 stdout : ligne seule");
	fprintf (stderr, "\n3 stderr : avant fflush(stdout)\n");
	fflush 	(stdout);
	fprintf (stderr, "\n4 stderr : apres fflush (stdout)\n");
	fprintf (stdout, "5 stdout : ligne seule ");
	fprintf (stderr, "\n6 stderr : avant fgets(stdin)\n");
	fgets (chaine, 10, stdin);
	fprintf (stderr, "\n7 stderr : apres fgets(stdin)\n");

	return (0);
}
