	#define	_XOPEN_SOURCE
	#include <limits.h>
	#include <locale.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>


	int
main (int argc, char * argv [])
{
	int		i;
	int		lg;
	time_t		heure;
	struct tm	tm;
	struct tm *	exemple;
	char * 		buffer;
	char *		retour;

	setlocale (LC_ALL, "");

	time (& heure);
	exemple = localtime (& heure);

	memset (& tm, 0, sizeof (struct tm));

	for (i = 1; i < argc ; i ++) {
		lg = strftime (NULL, SSIZE_MAX, argv [i], exemple);
		if (lg > 0) {
			/* On alloue 2 octets de plus pour \n et \0 */
			buffer = (char *) malloc (lg + 2);
			strftime (buffer, lg + 2, argv [i], exemple);
			fprintf (stdout, "Format %s (exemple %s) : ",
				argv [i], buffer);
			while (1) {
				fgets (buffer, lg + 2, stdin);
				retour = strptime (buffer, argv [i], & tm);
				if (retour == NULL)
					fprintf (stdout, "Erreur > ");
				else
					break;
			}
			free (buffer);
		}
	}
	puts (asctime (& tm));
	return (0);
}
