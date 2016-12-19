
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <signal.h>
	#include <sys/resource.h>


	int
main (void)
{
#ifdef NDEBUG
	struct rlimit limite;

	if (getrlimit (RLIMIT_CORE, & limite) != 0) {
		fprintf (stderr, "Impossible d'acc�der � RLIMIT_CORE\n");
		return (1);
	}

	limite . rlim_cur = 0;

	if (setrlimit (RLIMIT_CORE, & limite) != 0) {
		fprintf (stderr, "Impossible d'�crire RLIMIT_CORE\n");
		return (1);
	}
	
	fprintf (stdout, "Code d�finitif, \"core\" �vit� \n");
#else
	fprintf (stdout, "Code de d�veloppement, \"core\" cr�� si besoin\n");
#endif

	/*
         * Et maintenant... on se plante !
	 */

	raise (SIGSEGV);

	return (0);
}
