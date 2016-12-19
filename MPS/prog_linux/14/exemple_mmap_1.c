
	#include <fcntl.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/mman.h>



	int
main (int argc, char * argv [])
{
	char * 		projection;
	int		fichier;
	struct stat	etat_fichier;
	long		taille_fichier;
	int		i;
	char		tmp;

	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s fichier_a_inverser\n", argv [0]);
		exit (1);
	}
	if ((fichier = open (argv [1], O_RDWR)) < 0) {
		perror ("open");
		exit (1);
	}
	if (stat (argv [1], & etat_fichier) != 0) {
		perror ("stat");
		exit (1);
	}
	taille_fichier = etat_fichier.st_size;
	projection = (char *) mmap (NULL, taille_fichier,
				PROT_READ | PROT_WRITE, MAP_SHARED, fichier, 0);
	if (projection == (char *) MAP_FAILED) {
		perror ("mmap");
		exit (1);
	}
	close (fichier);
	for (i = 0; i < taille_fichier / 2; i ++) {
		tmp = projection [i];
		projection [i ] = projection [taille_fichier - i - 1];
		projection [taille_fichier - i - 1] = tmp;
	}
	munmap ((void *) projection, taille_fichier);
	return (0);
}
	
