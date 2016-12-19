
	#include <stdio.h>
	#include <stdlib.h>

	void	gestion_sortie (int code, void * pointeur);

	int
main (void)
{
	FILE * fp;

	fp = fopen ("exemple_atexit.c", "r");
	if (on_exit (gestion_sortie, (void *) fp) != 0)
		fprintf (stderr, "Erreur dans on_exit\n");

	fp = fopen ("exemple_on_exit.c", "r");
	if (on_exit (gestion_sortie, (void *) fp) != 0)
		fprintf (stderr, "Erreur dans on_exit\n");

	if (on_exit (gestion_sortie, NULL) != 0)
		fprintf (stderr, "Erreur dans on_exit\n");

	fprintf (stdout, "Allez... on quitte en revenant de main()\n");
	return (4);
}

	void
gestion_sortie (int code, void * pointeur)
{
	fprintf (stdout, "Gestion Sortie appelée... code %d\n", code);
	if (pointeur == NULL) {
		fprintf (stdout, "Pas de fichier à fermer\n");
	} else {
		fprintf (stdout, "Fermeture d'un fichier\n");
		fclose ((FILE *) pointeur);
	}
}

