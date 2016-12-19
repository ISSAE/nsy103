
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>


	int
main (void)
{
	FILE * fp;
	char   chaine [27];

	fprintf (stdout, "Création fichier\n");
	fp = fopen ("essai.unlink", "w+");
	if (fp == NULL) {
		perror ("fopen");
		exit (1);
	}
	fprintf (fp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	fflush (fp);
	system ("ls -l essai.unlink");
	fprintf (stdout, "Effacement fichier\n");
	if (unlink ("essai.unlink") < 0) {
		perror ("unlink");
		exit (1);
	}
	system ("ls -l essai.unlink");
	fprintf (stdout, "Relecture du contenu du fichier\n");
	if (fseek (fp, 0, SEEK_SET) < 0) {
		perror ("fseek");
		exit (1);
	}
	if (fgets (chaine, 27, fp) == NULL) {
		perror ("fgets");
		exit (1);
	}
	fprintf (stdout, "Lu : %s\n", chaine);
	fprintf (stdout, "Fermeture fichier\n");
	fclose (fp);
	return (0);
}

