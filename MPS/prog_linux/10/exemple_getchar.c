
	#include <stdio.h>
	#include <ctype.h>

	int
main (void)
{
	int	lu;
	char	caracteres [17];
	int	emplacement = 0;
	int	rang = 0;

	caracteres [16] = '\0';

	while ((lu = getchar()) != EOF) {
		if ((rang = emplacement % 16) == 0)
			fprintf (stdout, "%08X  ", emplacement % 0xFFFFFFFF);
		fprintf (stdout, "%02X", lu);
		if (rang == 7)
			fprintf (stdout, "-");
		else
			fprintf (stdout, " ");
		if (isprint (lu))
			caracteres [rang] = lu;
		else
			caracteres [rang] = ' ';
		if (rang == 15)
			fprintf (stdout, " %s\n", caracteres);
		emplacement ++;
	}
	while (rang < 15) {
		fprintf (stdout, "   ");
		caracteres [rang] = '\0';
		rang ++;
	}
	fprintf (stdout, " %s\n", caracteres);
	return (0);
}
