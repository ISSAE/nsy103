	#include <fcntl.h>
	#include <stdio.h>
	#include <unistd.h>


	int
main (void)
{
	int	tube [2];
	char	c = 'c';
	int	i;

	if (pipe (tube) != 0) {
		perror ("pipe");
		exit (1);
	}
	fcntl (tube [1], F_SETFL, O_NONBLOCK);
	i = 0;
	while (1) {
		if (write (tube [1], & c, 1) != 1) {
			perror ("write");
			sleep (1);
		} else
			i ++;
		fprintf (stdout, "%d octets écrits\n", i);
	}
	return (0);
}
