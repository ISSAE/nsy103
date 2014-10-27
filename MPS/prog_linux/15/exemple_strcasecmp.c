
	#include <stdio.h>
	#include <string.h>
	#include <locale.h>

	int
main (int argc, char * argv [])
{
	int	compar;

	setlocale (LC_ALL, "");

	if (argc != 3) {
		fprintf (stderr, "Syntaxe : %s chaine_1 chaine_2\n", argv [0]);
		exit (1);
	}
	compar = strcasecmp (argv [1], argv [2]);
	fprintf (stdout, "%s  %c %s \n", argv [1],
			(compar > 0 ? '>' : (compar == 0 ? '=' :  '<' )),
			argv [2]);
			
	return (0);
}
