
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/stat.h>

	int
main (void)
{
	int	tube [2];
	struct stat status;

	fprintf (stdout, "Création tube\n");
	if (pipe (tube) != 0) {
		perror ("pipe");
		exit (1);
	}
	if (fstat (tube [0], & status) != 0) {
		perror ("fstat");
		exit (1);
	}
	fprintf (stdout, "Status : ");
	if (S_ISFIFO (status .st_mode))
		fprintf (stdout, "FIFO\n");
	else
		fprintf (stdout, "? \n");
	return (0);
}
