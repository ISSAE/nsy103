
	#include <fcntl.h>
	#include <unistd.h>
	#include <stdio.h>

	int
main (void)
{
	int fd;
	fd = open ("essai.dup", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		perror ("open");
		exit (1);
	}
	close (STDOUT_FILENO);
	if (dup (fd) < 0) {
		perror ("dup");
		exit (1);
	}
	close (fd);
	execlp ("ls", "ls", NULL);
	perror ("execlp");
	exit (1);
}
