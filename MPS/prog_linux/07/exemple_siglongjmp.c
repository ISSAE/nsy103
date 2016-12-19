
	#include <stdio.h>
	#include <stdlib.h>
	#include <signal.h>
	#include <setjmp.h>

	sigjmp_buf	contexte;

	void
gestionnaire_sigfpe (int numero)
{
	siglongjmp (contexte, 1);
	/* Si l'on est ici le saut a raté, il faut quitter */
	signal (numero, SIG_DFL);
	raise (numero);
}

	int
main (void)
{
	int	p, q, r;

	signal (SIGFPE, gestionnaire_sigfpe);

	while (1) {
		if (sigsetjmp (contexte, 1) != 0) {
			/* On est arrivé ici par siglongjmp() */
			fprintf (stdout, "Aie ! erreur mathématique ! \n");
			fflush (stdout);
		}
		while (1) {
			fprintf (stdout, "Entrez le dividende p : ");
			if (fscanf (stdin, "%d", & p) == 1)
				break;
		}
		while (1) {
			fprintf (stdout, "Entrez le diviseur q : ");
			if (fscanf (stdin, "%d", & q) == 1)
				break;
		}
		r = p / q;
		fprintf (stdout, "rapport p / q = %d\n", r); 
	}
	return (0);
}
