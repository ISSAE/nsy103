	#include <ctype.h>
	#include <errno.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/resource.h>

	void
syntaxe (char * nom)
{
	fprintf (stderr, "Syntaxe : %s <classe> <identifiant>\n", nom);
	fprintf (stderr, "   <classe> = P (PID)\n");
	fprintf (stderr, "              G (PGID)\n");
	fprintf (stderr, "              U (UID)\n");
	exit (1);
}

	int
main (int argc, char * argv [])
{
	int	classe;
	int	identifiant;
	int	priorite;

	if (argc != 3)
		syntaxe (argv [0]);
	if (toupper (argv [1] [0]) == 'P')
		classe = PRIO_PROCESS;
	else if (toupper (argv [1] [0]) == 'G')
		classe = PRIO_PGRP;
	else if (toupper (argv [1] [0]) == 'U')
		classe = PRIO_USER;
	else
		syntaxe (argv [0]);
	if (sscanf (argv [2], "%d", & identifiant) != 1)
		syntaxe (argv [0]);
	errno = 0;
	priorite = getpriority (classe, identifiant);
	if ((priorite == -1) && (errno != 0))
		perror (argv [2]);
	else
		fprintf (stderr, "%d : %d\n", identifiant, priorite);
	return (0);
}

