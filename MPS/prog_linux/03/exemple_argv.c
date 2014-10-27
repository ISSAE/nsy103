
	#include <stdio.h>


	int
main (int argc, char * argv [])
{
	int	i;

	fprintf (stdout, "%s a reçu en argument :\n", argv [0]);
	for (i = 1; i < argc; i ++)
		fprintf (stdout, "  %s\n", argv [i]);
	return (0);
}
