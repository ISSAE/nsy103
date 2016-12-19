
	#include <stdio.h>

	int
main (int argc, char * argv [])
{
	int	i;

	if (argc == 1) {
		puts ("Pas d'argument\n");
	} else {
		puts ("Arguments : ");
		for (i = 1; i < argc; i ++)
			puts (argv [i]);
		puts ("\n");
	}
	return (0);
}
		

