	#include <stdio.h>

	int
main (int argc, char * argv [])
{
	unsigned short int s_i;
	unsigned char *    ch;
	int                i;

	if ((argc != 2) || (sscanf (argv [1], "%hi", & s_i) != 1)) {
		fprintf (stderr, "Syntaxe : %s entier \n", argv [0]);
		exit (1);
	}
	ch = (unsigned char *) & s_i;
	fprintf (stdout, "%04X représenté ainsi ", s_i);
	for (i = 0; i < sizeof (short int); i ++)
		fprintf (stdout, "%02X ", ch [i]);
	fprintf (stdout, "\n");
	return (0);
}

