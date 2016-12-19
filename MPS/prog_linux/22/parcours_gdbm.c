	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <gdbm.h>

	void affiche_contributeur (datum cle, datum donnee);
	
	
	int
main (int argc,char * argv [])
{
	GDBM_FILE base;
	datum  cle;
	datum  donnee;
	
	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s nom_base \n", argv [0]);
		exit (1);
	}
	if ((base = gdbm_open (argv [1], 0, GDBM_READER, 0, NULL)) == NULL ) {
		fprintf (stderr, "%s :%s\n", argv [1], gdbm_strerror (gdbm_errno));
		exit (1);
	}
	for (cle = gdbm_firstkey (base); cle . dptr != NULL; cle = gdbm_nextkey (base, cle)) {
		donnee = gdbm_fetch (base, cle);
		if (donnee . dptr != NULL)
			affiche_contributeur (cle, donnee);
	}
	gdbm_close (base);
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
