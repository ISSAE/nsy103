	#include <stdio.h>
	#include <unistd.h>

	int
main (void)
{
	if (isatty (STDIN_FILENO))
		fprintf (stdout, "stdin : %s\n", ttyname (STDIN_FILENO));
	else
		fprintf (stdout, "stdin : Pas un terminal ! \n");
	fprintf (stdout, "Terminal de contrôle : %s\n", ctermid (NULL));
	return (0);
}
