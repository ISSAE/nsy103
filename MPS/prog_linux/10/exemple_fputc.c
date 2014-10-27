
	#include <stdio.h>
	#include <limits.h>

	void	test_fputc (int valeur, FILE * fp);

	int
main (void)
{
	test_fputc ('A', stdout);
	test_fputc (65, stdout);
	test_fputc (UCHAR_MAX, stdout);
	test_fputc (-1, stdout);
	test_fputc ('A', stdin);
	return (0);
}

	void
test_fputc (int valeur, FILE * fp)
{
	int	retour;

	retour = fputc (valeur, fp);

	fprintf (stdout, "\n Ecrit : %d, ", valeur);
	fprintf (stdout, "retour = %d ", retour);
	if (retour == EOF)
		fprintf (stdout, "(EOF)");
	fprintf (stdout, "\n");
}
