	#include <fcntl.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <gdbm/ndbm.h>

	void affiche_contributeur (datum cle, datum donnee);
	
	
	int
main (int argc,char * argv [])
{
	datum  cle;
	datum  donnee;
	DBM *  dbm;
	
	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s nom_base \n", argv [0]);
		exit (1);
	}
	if ((dbm = dbm_open (argv [1], O_RDONLY, 0)) == NULL) {
		perror ("dbm_open");
		exit (1);
	}
	for (cle = dbm_firstkey (dbm); cle . dptr != NULL; cle = dbm_nextkey (dbm, cle)) {
		donnee = dbm_fetch (dbm, cle);
		if (donnee . dptr != NULL)
			affiche_contributeur (cle, donnee);
	}
fprintf (stdout, "F = %d\n", dbm_pagfno());
	dbm_close (dbm);
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
