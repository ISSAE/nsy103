	#include <fcntl.h>
	#include <stdio.h>
	#include <unistd.h>

	int
main (int argc, char * argv [])
{
	int fd;
	char buffer [256];
	int i,j;

	if (argc != 3) {
		fprintf (stderr, "Syntaxe : %s fichier sync \n", argv [0]);
		exit (1);
	}
	if ((argv [2] [0] == 'o') || (argv [2] [0] == 'O')) {
		fprintf (stdout, "Écritures synchronisées \n");
		if ((fd = open (argv [1], O_RDWR | O_CREAT | O_SYNC, 0644)) < 0) {
			perror ("open");
			exit (1);
		}
	} else {
		fprintf (stdout, "Écritures non-synchronisées \n");
		if ((fd = open (argv [1], O_RDWR | O_CREAT, 0644)) < 0) {
			perror ("open");
			exit (1);
		}
	}
	for (i = 0; i < 1024; i ++) 
		for (j = 0; j < 256; j ++)
			if (write (fd, buffer, 256) < 0) {
				perror ("write");
				exit (1);
			}
	fsync (fd);
	close (fd);
	return (0);
}
