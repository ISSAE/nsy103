	#include <locale.h>
	#include <monetary.h>
	#include <stdio.h>

	int
main (void)
{
	int quantite [] = {
		1, 4, 3, 1, 1, 2, 0
	};
	char * reference [] = {
		"ABC", "DEF", "GHI", "JKL", "MNO", "PQR", NULL
	};
	double prix [] = {
		1500, 2040, 560, 2500, 38400, 125, 0
	};
	int i;
	char format [80];
	double total = 0.0;


	setlocale (LC_ALL, "");
	
	for (i = 0; reference [i] != NULL; i ++) {
		strfmon (format, 80, "%%5s : %#5n x %%d = %#5n\n",
				prix [i], prix [i] * quantite [i]);
		fprintf (stdout, format, reference [i], quantite [i]);
		total += prix [i] * quantite [i];
	}
	strfmon (format, 80, "                  Total = %#5n\n", total);
	fprintf (stdout, format);
	return (0);
}

		
