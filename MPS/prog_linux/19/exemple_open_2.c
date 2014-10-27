
	#include <fcntl.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>

	int
main (void)
{
	int	fd;

	if ((fd = open ("essai.open", O_RDWR | O_CREAT | O_EXCL, 0777)) < 0)
		perror ("open");
	else
		close (fd);
	return (0);
}
