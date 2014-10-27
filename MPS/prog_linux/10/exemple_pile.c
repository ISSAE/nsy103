
	#include <stdio.h>

	int	fonction (int x);

	int
main (void)
{
	return (fonction (1));
}

	int
fonction (int x)
{
	int x1;
	char chaine [128];

	fprintf (stdout, "& x    = %p lg = %d\n", & x, sizeof (x));
	fprintf (stdout, "& x1   = %p lg = %d\n", & x1, sizeof (x1));
	fprintf (stdout, "chaine = %p lg = %d\n", chaine, sizeof (chaine));
	if (x > 0)
		return (fonction (x - 1));
	return (0);
}

