	#include <locale.h>
	#include <stdio.h>

	int
main (void)
{
	setlocale (LC_ALL, "");
	fprintf (stdout, "LC_COLLATE  = %s \n", setlocale (LC_COLLATE,  NULL));
	fprintf (stdout, "LC_CTYPE    = %s \n", setlocale (LC_CTYPE,    NULL));
	fprintf (stdout, "LC_MESSAGES = %s \n", setlocale (LC_MESSAGES, NULL));
	fprintf (stdout, "LC_MONETARY = %s \n", setlocale (LC_MONETARY, NULL));
	fprintf (stdout, "LC_NUMERIC  = %s \n", setlocale (LC_NUMERIC,  NULL));
	fprintf (stdout, "LC_TIME     = %s \n", setlocale (LC_TIME,     NULL));
	fprintf (stdout, "LC_ALL      = %s \n", setlocale (LC_ALL,      NULL));
	return (0);
}
