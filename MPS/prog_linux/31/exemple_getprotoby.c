	#include <netdb.h>
	#include <stdio.h>

	int
main (int argc, char * argv [])
{
	int               i, j;
	int               numero;
	struct protoent * proto;

	for (i = 1; i < argc; i ++) {
		if (sscanf (argv [i], "%d", & numero) == 1)
			proto = getprotobynumber (numero);
		else
			proto = getprotobyname (argv [i]);
		fprintf (stdout, "%s : ", argv [i]);
		if (proto == NULL) {
			fprintf (stdout, "inconnu \n");
			continue;
		}
		fprintf (stdout, "%s ( ", proto -> p_name);
		for (j = 0; proto -> p_aliases [j] != NULL; j ++)
			fprintf (stdout, "%s ", proto -> p_aliases [j]);
		fprintf (stdout, ") numéro = %d \n", proto -> p_proto);
	}
	return (0);
}
