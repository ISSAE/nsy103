
	#include <limits.h>
	#include <locale.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>

	int
main (int argc, char * argv [])
{
	int	i;
	size_t	lg;
	char *  buffer;
	struct tm *	tm;
	time_t		heure;

	setlocale (LC_ALL, "");

	time (& heure);
	tm = localtime (& heure);

	for (i = 1; i < argc; i ++) {
		fprintf (stdout, "%s : ", argv [i]);
		lg = strftime (NULL, SSIZE_MAX, argv [i], tm);
		if (lg > 0) {
			buffer = (char *) malloc (lg + 1);
			if (buffer == NULL) {
				perror ("malloc");
				exit (1);
			}
			strftime (buffer, lg + 1, argv [i], tm);
			fprintf (stdout, "%s", buffer);
			free (buffer);
		}
		fprintf (stdout, "\n");
	}
	return (0);
}
