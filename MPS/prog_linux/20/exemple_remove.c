
	#include <stdio.h>

	int
main (int argc, char * argv [])
{
	char	chaine [5];
	int	i;

	for (i = 1; i < argc; i ++) {
		fprintf (stderr, "Effacer %s ? ", argv [i]);
		if (fgets (chaine, 5, stdin) == NULL)
			break;
		if ((chaine [0] != 'o') && (chaine [0] != 'O'))
			continue;
		if (remove (argv [i]) < 0)
			perror (argv [i]);
	}
	return (0);
}
