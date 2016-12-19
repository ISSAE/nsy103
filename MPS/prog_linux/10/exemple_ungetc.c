
	#include <ctype.h>
	#include <stdio.h>

	void	lecture_numerique	(FILE * fp);
	void	lecture_alphabetique	(FILE * fp);

	int
main (void)
{
	int	c;

	while ((c = getc (stdin)) != EOF) {
		if (isdigit (c)) {
			ungetc (c, stdin);
			lecture_numerique (stdin);
		} else if (isalpha (c)) {
			ungetc (c, stdin);
			lecture_alphabetique (stdin);
		}
	}
	return (0);
}

	void
lecture_numerique (FILE * fp)
{
	int	c;
	fprintf (stdout, "Lecture numérique : ");
	while (1) {
		c = getc (fp);
		if (! isdigit (c))
			break;
		fprintf (stdout, "%c", c);
	}
	ungetc (c, fp);
	fprintf (stdout, "\n");
}

	
	void
lecture_alphabetique (FILE * fp)
{
	int	c;
	fprintf (stdout, "Lecture alphabétique : ");
	while (1) {
		c = getc (fp);
		if (! isalpha (c))
			break;
		fprintf (stdout, "%c", c);
	}
	ungetc (c, fp);
	fprintf (stdout, "\n");
}

