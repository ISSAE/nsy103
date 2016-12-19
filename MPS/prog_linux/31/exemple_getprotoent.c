	#include <stdio.h>
	#include <netdb.h>

	int
main (void)
{
	struct protoent * proto;
	setprotoent (0);
	while ((proto = getprotoent ()) != NULL)
		fprintf (stdout, "%s ", proto -> p_name);
	endprotoent ();
	fprintf (stdout, "\n");
	return (0);
}
