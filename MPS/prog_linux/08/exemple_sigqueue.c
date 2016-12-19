	#include <signal.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

	void
syntaxe (const char * nom)
{
	fprintf (stderr, "syntaxe %s signal pid...\n", nom);
	exit (1);
}

	int
main (int argc, char * argv [])
{
	int     i;
	int     numero;
	pid_t   pid;
	union sigval valeur;

	if (argc == 1)
		syntaxe(argv [0]);
	i = 1;
	if (argc == 2) {
		numero = SIGTERM;
	} else {
		if (sscanf (argv [i], "%d", & numero) != 1)
			syntaxe(argv [0]);
		i ++;
	}
	if ((numero < 0) || (numero > NSIG - 1))
		syntaxe(argv [0]);
	valeur . sival_int = 0;
	for (; i < argc; i ++) {
		if (sscanf (argv [i], "%d", & pid) != 1)
			syntaxe(argv [0]);
		if (sigqueue (pid, numero, valeur) < 0) {
			fprintf (stderr, "%u : ", pid);
			perror ("");
		}
	}
	return (0);
}

