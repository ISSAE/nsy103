
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

	void
lecture_contenu (const char * nom)
{
	char *  buffer = NULL;
	char *  nouveau = NULL;
	int	taille = 0;
	int	nb_copies;

	while (1) {
		taille += 16;
		if ((nouveau = realloc (buffer, taille)) == NULL) {
			perror (nom);
			break;
		}
		buffer = nouveau;
		if ((nb_copies = readlink (nom, buffer, taille - 1)) == -1) {
			perror (nom);
			break;
		}
		if (nb_copies < taille - 1) {
			buffer [nb_copies] = '\0';
			fprintf (stdout, "%s : %s\n", nom, buffer);
			break;
		}
	}
	if (buffer != NULL)
		free (buffer);
}

	int
main (int argc, char * argv [])
{
	int 	i;
	for (i = 1; i < argc; i ++)
		lecture_contenu (argv [i]);
	return (0);
}

