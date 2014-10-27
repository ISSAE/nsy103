
	#define FILE_OFFSET_BITS	64

	#include <stdio.h>

	int
main (int argc, char * argv [])
{
	int	i;
	FILE	* fp;
	int	caractere;
	int	echange;

	off_t	debut;
	off_t	fin;

	if (argc < 2) {
		fprintf (stderr, "syntaxe : %s fichier...\n", argv [0]);
		exit (1);
	}
	for (i = 1; i < argc ; i ++) {
		if ((fp = fopen (argv [i], "r+")) == NULL) {
			fprintf (stderr, "%s inaccessible\n", argv [i]);
			continue;
		}
		if (fseek (fp, 0, SEEK_END) != 0) {
			fprintf (stderr, "%s non positionnable\n", argv [i]);
			fclose (fp);
			continue;
		}
		fin = ftell (fp) - 1;
		debut = 0;
		while (fin > debut) {
			if (fseek (fp, fin, SEEK_SET) != 0)
				break;
			caractere = fgetc (fp);
			if (fseek (fp, debut, SEEK_SET) != 0)
				break;
			echange = fgetc (fp);
			if (fseek (fp, debut, SEEK_SET) != 0)
				break;
			fputc (caractere, fp);
			if (fseek (fp, fin, SEEK_SET) != 0)
				break;
			fputc (echange, fp);
			fin --;
			debut ++;	
		}
		fclose (fp);
	}
	return (0);
}
