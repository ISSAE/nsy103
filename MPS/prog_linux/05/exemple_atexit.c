
	#include <stdio.h>
	#include <stdlib.h>

	void	sortie_1	(void);
	void	sortie_2	(void);
	void	sortie_3	(void);

	int
main (void)
{
	if (atexit (sortie_3) != 0)
		fprintf (stderr, "Impossible d'enregistrer sortie_3()\n");
	if (atexit (sortie_2) != 0)
		fprintf (stderr, "Impossible d'enregistrer sortie_2()\n");
	if (atexit (sortie_2) != 0)
		fprintf (stderr, "Impossible d'enregistrer sortie_2()\n");
	if (atexit (sortie_1) != 0)
		fprintf (stderr, "Impossible d'enregistrer sortie_1()\n");
	fprintf (stdout, "Allez... on quitte en revenant de main()\n");
	return (0);
}

	void
sortie_1 (void)
{
	fprintf (stdout, "Sortie_1 : apelle exit()\n");
	exit (0);
}

	void
sortie_2 (void)
{
	fprintf (stdout, "Sortie_2\n");
}

	void
sortie_3 (void)
{
	fprintf (stdout, "Sortie_3\n");
}

