	#define _GNU_SOURCE
	#include <stdio.h>
	#include <netdb.h>

	int
main (void)
{
	struct servent service;
	struct servent * retour;
	char           buffer [256];
	
	setservent (0);
	while (getservent_r (& service, buffer, 256, & retour) == 0)
		fprintf (stdout, "%s ", service . s_name);
	endservent ();
	fprintf (stdout, "\n");
	return (0);
}
