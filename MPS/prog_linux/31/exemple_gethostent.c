	#include <stdio.h>
	#include <netdb.h>

	int
main (void)
{
	struct hostent * hote;
	sethostent (1);
	while ((hote = gethostent ()) != NULL)
		fprintf (stdout, "%s ", hote -> h_name);
	fprintf (stdout, "\n");
	endhostent ();
	return (0);
}
