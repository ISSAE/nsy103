	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <gdbm/dbm.h>

	void affiche_contributeur (datum cle, datum donnee);
	
	
	int
main (int argc,char * argv [])
{
	datum  cle;
	datum  donnee;
	int    i;
	int    numero;
	
	if (argc < 2) {
		fprintf (stderr, "Syntaxe : %s nom_base clés...\n", argv [0]);
		exit (1);
	}
	if (dbminit (argv [1]) != 0) {
		perror ("dbminit");
		exit (1);
	}
	for (i = 2; i < argc; i ++) {
		if (sscanf (argv [i], "%d", & numero) == 1) {
			cle . dptr = (char *) (& numero);
			cle . dsize = sizeof (int);
			donnee = fetch (cle);
			if (donnee . dptr != NULL)
				affiche_contributeur (cle, donnee);
			else
				fprintf (stderr, "%s : inconnu\n", argv [i]);
		}	
	}
	dbmclose ();
	return (0);
}

	void
affiche_contributeur (datum cle, datum donnee)
{
	char * nom;
	char * email;
	char * web;
	
	nom = donnee . dptr;
	email = & (nom   [strlen (nom)   + 1]);
	web   = & (email [strlen (email) + 1]);

	fprintf (stdout, "Numero : %d\n", * ((int *) cle . dptr));
	fprintf (stdout, "  Nom      : %s\n", nom); 
	fprintf (stdout, "  Email    : %s\n", email);
	fprintf (stdout, "  Web      : %s\n", web);
}
