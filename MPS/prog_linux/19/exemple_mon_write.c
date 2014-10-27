
	#include <errno.h>
	#include <fcntl.h>
	#include <stdio.h>
	#include <unistd.h>

	#include <sys/stat.h>
	#include <sys/types.h>



	ssize_t
mon_write (int fd, const void * buffer, size_t taille)
{
	const void *	debut	= buffer;
	size_t		restant	= taille;
	ssize_t		ecrits	= 0;

	while (restant > 0) {
	
		while ((ecrits = write (fd, debut, restant)) == -1) {
			if (errno == EINTR)
				continue;
			if (errno !=EAGAIN)
				return (-1);
			sleep (1);
		}
		restant -= ecrits;
		debut += ecrits;
	}
	return (taille);
}

	int
main (void)
{
	int	lus;
	char	bloc [BUFSIZ];

	while (1) {
		while ((lus = read (STDIN_FILENO, bloc, BUFSIZ)) == -1) {
			if (errno == EINTR)
				continue;
			if (errno != EAGAIN) {
				perror ("read");
				return (1);
			}
			sleep (1);
		}
		if (lus == 0)
			return (0);
		if (mon_write (STDOUT_FILENO, bloc, lus) < 0) {
			perror ("write");
			exit (1);
		}
	}
	return (0);
}


