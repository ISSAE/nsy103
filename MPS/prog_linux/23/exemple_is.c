	#include <ctype.h>
	#include <locale.h>
	#include <stdio.h>

	void
affiche_caracteristiques (int c)
{
	fprintf (stdout, "%02X : ", (unsigned char) c);
	if (isalnum (c))	fprintf (stdout, "alphanumérique ");
	if (isalpha (c))	fprintf (stdout, "alphabétique ");
	if (isascii (c))	fprintf (stdout, "ascii ");
	if (iscntrl (c))	fprintf (stdout, "contrôle ");
	if (isdigit (c))	fprintf (stdout, "chiffre ");
	if (isgraph (c))	fprintf (stdout, "graphique ");
	if (islower (c))	fprintf (stdout, "minuscule ");
	if (isprint (c))	fprintf (stdout, "imprimable ");
	if (ispunct (c))	fprintf (stdout, "ponctuation ");
	if (isspace (c))	fprintf (stdout, "espace ");
	if (isupper (c))	fprintf (stdout, "majuscule ");
	if (isxdigit (c))	fprintf (stdout, "héxadécimal ");
	fprintf (stdout, "\n");
}

	int
main (void)
{
	char chaine [128];
	int  i;
	setlocale (LC_ALL, "");
	while (fgets (chaine, 128, stdin) != NULL)
		for (i = 0; i < strlen (chaine); i ++)
			affiche_caracteristiques (chaine [i]);
	return (0);
}
