
	#include <fcntl.h>
	#include <stdio.h>
	#include <unistd.h>


	int
main (int argc, char * argv [])
{
	char 		chaine [80];
	int		fd;
	struct flock	flock;
	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s nom_fichier\n", argv [0]);
		exit (1);
	}

	fd = open (argv [1], O_RDWR | O_CREAT | O_EXCL, 02644);	
	if (fd < 0) {
		perror ("open");
		exit (1);
	}

	write (fd, "ABCDEFGHIJ", 10);

	flock . l_type = F_WRLCK;
	flock . l_start = 0;
	flock . l_whence = SEEK_SET;
	flock . l_len = 10;

	if (fcntl (fd, F_SETLK, & flock) < 0) {
		perror ("fcntl");	
		exit (1);
	}
	fprintf (stdout, "Verrou installé\n");
	fgets (chaine, 80, stdin);
	close (fd);
	return (0);
}

