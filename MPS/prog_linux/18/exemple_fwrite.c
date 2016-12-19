
	#include <stdio.h>
	#include <stdlib.h>

	typedef struct {
		double	x;
		double	y;
		double	z;
	} point_t;

	int
main (void)
{
	point_t *	table;
	int		n;
	int		i;
	FILE *		fp;

	n = 8;
	table = (point_t *) calloc (n, sizeof (point_t));
	if (table == NULL) {
		perror ("calloc");
		exit (1);
	}

	/* Initialisation */
	table [0].x = -1.0; table [0].y = -1.0; table [0].z = -1.0;
	table [1].x =  1.0; table [1].y = -1.0; table [1].z = -1.0;
	table [2].x = -1.0; table [2].y =  1.0; table [2].z = -1.0;
	table [3].x =  1.0; table [3].y =  1.0; table [3].z = -1.0;
	table [4].x = -1.0; table [4].y = -1.0; table [4].z =  1.0;
	table [5].x =  1.0; table [5].y = -1.0; table [5].z =  1.0;
	table [6].x = -1.0; table [6].y =  1.0; table [6].z =  1.0;
	table [7].x =  1.0; table [7].y =  1.0; table [7].z =  1.0;

	/* Sauvegarde */
	if ((fp = fopen ("essai.fread", "w")) == NULL) {
		perror ("fopen");
		exit (1);
	}
	/* Ecriture du nombre de points, suivi de la table */
	if ((fwrite (& n, sizeof (int), 1, fp) != 1)
	 || (fwrite (table, sizeof (point_t), 8, fp) != 8)) {
		perror ("fwrite");
		exit (1);
	}
	fclose (fp);
	free (table);
	table = NULL;
	n = 0;

	/* Récupération */
	if ((fp = fopen ("essai.fread", "r")) == NULL) {
		perror ("fopen");
		exit (1);
	}
	if (fread (& n, sizeof (int), 1, fp) != 1) {
		perror ("fread");
		exit (1);
	}
	if ((table = (point_t *) calloc (n, sizeof (point_t))) == NULL) {
		perror ("calloc");
		exit (1);
	}
	if (fread (table, sizeof (point_t), n, fp) != 8) {
		perror ("fread");
		exit (1);
	}
	fclose (fp);

	/* Affichage */
	for (i = 0; i < n; i ++)
		fprintf (stdout, "point [%d] : % f, % f, % f\n",
			i, table [i].x, table [i].y, table [i].z);

	return (0);
}
