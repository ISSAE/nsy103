
	#include <stdio.h>
	#include <stdlib.h>

	#define	NB_BLOCS	257
	#define TAILLE		(1024*1024)

	int
main (void)
{

	int	i;
	char *	bloc [NB_BLOCS];

	for (i = 0; i < NB_BLOCS; i ++) {
		if ((bloc [i] = (char *) malloc (TAILLE)) == NULL) {
			fprintf (stderr, "Echec pour i = %d\n", i);
			break;
		}
		fprintf (stderr, "Remplissage de %d\n", i);
		memset (bloc [i], 0, TAILLE);
	}
	fprintf (stderr, "Alloués : %d blocs\n", i);
	
	return (0);
}	

