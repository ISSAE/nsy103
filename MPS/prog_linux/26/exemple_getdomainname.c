	#include <errno.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

	int
main (void)
{
	char * buffer = NULL;
	size_t taille = 8;

	buffer = malloc (taille);

	while (getdomainname (buffer, taille) != 0) {
		if (errno != ENAMETOOLONG) {
			perror ("getdomainname");
			return (1);
		}
		taille += 8;
		buffer = realloc (buffer, taille);
	}
	fprintf (stdout, "%s\n", buffer);
	free (buffer);
	return (0);
}
