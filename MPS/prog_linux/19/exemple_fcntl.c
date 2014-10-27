
	#include <fcntl.h>
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include <sys/types.h>

	int
main (int argc, char * argv[])
{
	int	fd;
	int	etat;

	if ((argc != 2) 
	 || ((strcasecmp (argv [1], "ferme") != 0)
	  && (strcasecmp (argv [1], "laisse") != 0))) {
		fprintf (stderr, "syntaxe : %s [ferme|laisse]\n", argv [0]);
		exit (1);
	}

	fd = open ("essai.fcntl", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		perror ("open");
		exit (1);
	}
	if ((etat = fcntl (fd, F_GETFD)) < 0) {	
		perror ("fcntl");
		exit (1);
	}
	if (strcasecmp (argv [1] , "ferme") == 0)
		etat |= FD_CLOEXEC;
	else 
		etat &= ~FD_CLOEXEC;
	if (fcntl (fd, F_SETFD, etat) < 0) {
		perror ("fcntl");
		exit (1);
	}
	execlp ("fuser", "fuser", "-a", "essai.fcntl", NULL);
	perror ("execlp");
	exit (1);
}
