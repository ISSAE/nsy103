	#include <stdio.h>
	#include <stdlib.h>

	int
main (void)
{
	char chaine [128];
	while (fgets (chaine, 128, stdin) != NULL)
		fprintf (stdout, "Lu : %d \n", atoi (chaine));
	return (0);
}
