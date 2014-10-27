	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/types.h>

	#define	NB_FILS	10

	int
main (void)
{
	int	tube [NB_FILS] [2];
	int	i, fils;
	char	c = 'c';
	fd_set	ensemble;

	for (i = 0; i < NB_FILS; i ++)
		if (pipe (tube [i]) < 0) {
			perror ("pipe");
			exit (1);
		}
	for (fils = 0; fils < NB_FILS; fils ++)
		if (fork () == 0)
			break;
	for (i = 0; i < NB_FILS; i ++)
		if (fils == NB_FILS) {
			/* On est dans le père */
			close (tube [i] [1]);
		} else {
			close (tube [i] [0]);
			if (i != fils)
				close (tube [i] [1]);
		}
	if (fils == NB_FILS) {
		while (1) {
			FD_ZERO (& ensemble);
			for (i = 0; i < NB_FILS; i ++)
				FD_SET (tube [i] [0], & ensemble);
			if (select (FD_SETSIZE, & ensemble, NULL, NULL, NULL) <= 0) {
				perror ("select");
				break;
			}
			for (i = 0; i < NB_FILS; i ++)
			 	if (FD_ISSET (tube [i] [0], & ensemble)) {
					fprintf (stdout, "%d ", i);
					fflush (stdout);
					read (tube [i] [0], & c, 1);
				}
		}
	} else {
		while (1) {
			usleep ((fils + 1) * 1000000);
			write (tube [fils] [1], & c, 1);
		}
	}
	return (0);
}
			
