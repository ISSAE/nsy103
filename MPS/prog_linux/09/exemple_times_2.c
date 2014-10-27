
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <time.h>
	#include <sys/times.h>
	
	int
main (int argc, char * argv [])
{
	struct tms mesure;
	double duree;

	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s <commande>\n", argv [0]);
		exit (1);

	}
	system (argv [1]);
	times (& mesure);
	duree = mesure . tms_cutime;
	duree = duree / CLK_TCK;
	fprintf (stdout, "Temps CPU mode utilisateur = %f\n", duree);
	duree = mesure . tms_cstime;
	duree = duree / CLK_TCK;
	fprintf (stdout, "Temps CPU en mode noyau    = %f\n", duree);
	return (0);
}
