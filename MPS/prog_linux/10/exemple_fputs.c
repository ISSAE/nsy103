
	#include <stdio.h>

	int
main (int argc, char * argv [])
{
	int	i;

	if (argc == 1) {
		fputs ("Pas d'argument\n", stdout);
	} else {
		fputs ("Arguments : ", stdout);
		for (i = 1; i < argc; i ++)
			fputs (argv [i], stdout);
		fputs ("\n", stdout);
	}
	return (0);
}
		

