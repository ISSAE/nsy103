
	#include <stdio.h>
	#include <stdlib.h>

	#define	NB_BLOCS	(1024*1024)
	#define TAILLE		257

	int
main (void)
{

	int	i;
	char *	bloc [NB_BLOCS];

	for (i = 0; i < NB_BLOCS; i ++) {
		if ((bloc [i] = (char *) calloc (1, TAILLE)) == NULL) {
			fprintf (stderr, "Echec pour i = %d\n", i);
			break;
		}
	}
	fprintf (stderr, "Alloués : %d blocs de %d Ko\n", i, TAILLE / 1024);
	
	return (0);
}	

