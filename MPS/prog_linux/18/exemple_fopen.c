
	#include <stdio.h>

	void
ouverture (char * nom, char * mode)
{
	FILE * fp;
	fprintf (stderr, "fopen (%s, %s) : ", nom, mode);
	if ((fp = fopen (nom, mode)) == NULL) {
		perror ("");
	} else {
		fprintf (stderr, "Ok\n");
		fclose (fp);
	}
}

	int
main (void)
{
	ouverture ("/etc/inittab", "r");
	ouverture ("/etc/inittab", "w");
	ouverture ("essai.fopen",  "r");
	ouverture ("essai.fopen",  "w");
	ouverture ("essai.fopen",  "r");
	return (0);
}	
