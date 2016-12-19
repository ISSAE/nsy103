
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
		fprintf (stderr, "Impossible d'accéder à RLIMIT_CORE\n");
		return (1);
	}

	limite . rlim_cur = 0;

	if (setrlimit (RLIMIT_CORE, & limite) != 0) {
		fprintf (stderr, "Impossible d'écrire RLIMIT_CORE\n");
		return (1);
	}
	
	fprintf (stdout, "Code définitif, \"core\" évité \n");
#else
	fprintf (stdout, "Code de développement, \"core\" créé si besoin\n");
#endif

	/*
         * Et maintenant... on se plante !
	 */

	raise (SIGSEGV);

	return (0);
}
