
	#include <stdio.h>


	int
main (void)
{
	int	caractere;
	off_t	trou;

	if (fseeko (stdout, 0, SEEK_SET) < 0) {
		fprintf (stderr, "Pas de possibilité de création de trou\n");
		while ((caractere = getchar ()) != EOF)
			putchar (caractere);
		return (0);
	}

	trou = 0;
	while ((caractere = getchar ()) != EOF) {
		if (caractere == 0) {
			trou ++;
			continue;
		}
		if (trou != 0) {
			fseeko (stdout, trou, SEEK_CUR);
			trou = 0;
		}
		putchar (caractere);
	}
	if (trou != 0) {
		fseeko (stdout, trou - 1, SEEK_CUR);
		putchar (0);
	}
	return (0);
}
