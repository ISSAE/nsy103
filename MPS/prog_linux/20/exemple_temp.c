
	#include <stdio.h>
	#include <stdlib.h>



	int
main (void)
{
	char *	nom_tempnam;
	char	nom_tmpnam [L_tmpnam];
	char	nom_mktemp [20];

	nom_tempnam = tempnam (NULL, "abcdef");
	fprintf (stderr, "tempnam (NULL, \"abcdef\") = ");
	if (nom_tempnam == NULL)
		perror ("NULL");
	else 
		fprintf (stderr, "%s\n", nom_tempnam);
	free (nom_tempnam);

	fprintf (stderr, "tmpnam () = ");
	if (tmpnam (nom_tmpnam) == NULL)
		perror ("NULL");
	else
		fprintf (stderr, "%s\n", nom_tmpnam);

	strcpy (nom_mktemp, "/tmp/abcdefXXXXXX");
	fprintf (stderr, "mktemp (\"/tmp/abcdefXXXXXX\") = ");
	if (mktemp (nom_mktemp) == NULL)
		perror ("NULL");
	else
		fprintf (stderr, "%s\n", nom_mktemp);

	return (0);
}			
	
