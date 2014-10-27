
	#include <stdio.h>

	int
main ()
{
	int	i;

	while ((i = fgetc (stdin)) != EOF)
		fprintf (stdout, " %02X\n", i);

	return (0);
}
