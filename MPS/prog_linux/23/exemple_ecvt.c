	#include <stdio.h>
	#include <stdlib.h>

	int
main (int argc, char * argv[])
{
	double valeur;
	int    nb_chiffres;
	int    position;
	int    signe;
	char * retour;
	
	if ((argc != 3) 
	 || (sscanf (argv [1], "%lf", & valeur) != 1)
	 || (sscanf (argv [2], "%d", & nb_chiffres) != 1)) {
		fprintf (stderr, "Syntaxe : %s valeur nb_chiffres \n",
				argv [0]);
		exit (1);
	}
	retour = ecvt (valeur, nb_chiffres, & position, & signe);
	fprintf (stdout, "ecvt() = %s \n", retour);
	fprintf (stdout, "    position = %d \n", position);
	fprintf (stdout, "    signe = %d \n", signe);

	retour = fcvt (valeur, nb_chiffres, & position, & signe);
	fprintf (stdout, "fcvt() = %s \n", retour);
	fprintf (stdout, "    position = %d \n", position);
	fprintf (stdout, "    signe = %d \n", signe);

	return (0);
}
