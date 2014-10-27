
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <signal.h>
	#include <errno.h>

	void
gestionnaire (int numero)
{
	stack_t pile;

	fprintf (stdout, "\nSignal %d reçu\n", numero);

	if (sigaltstack (NULL, & pile) != 0) {
		fprintf (stderr, "Erreur sigaltstack %d\n", errno);
		return;
	}
	if (pile . ss_flags & SS_DISABLE)
		fprintf (stdout, "La pile spéciale est inactive\n");
	else
		fprintf (stdout, "La pile spéciale est active\n");

	if (pile . ss_flags & SS_ONSTACK)
		fprintf (stdout, "Pile spéciale en cours d'utilisation\n");
	else
		fprintf (stdout, "Pile spéciale pas utilisée actuellement\n");
}

	int
main (void)
{
	stack_t pile;
	struct sigaction action;
	
	if ((pile . ss_sp = malloc (SIGSTKSZ)) == NULL) {
		fprintf (stderr, "Pas assez de mémoire\n");
		exit (1);
	}
	pile . ss_size = SIGSTKSZ;
	pile . ss_flags = 0;

	if (sigaltstack (& pile, NULL) != 0) {
		fprintf (stderr, "Erreur sigaltstack() %d\n", errno);
		exit (1);
	}

	action . sa_handler = gestionnaire;
	sigemptyset (& (action . sa_mask));
	action . sa_flags = SA_RESTART | SA_ONSTACK;
	if (sigaction (SIGQUIT, & action, NULL) != 0) {
		fprintf (stderr, "Erreur sigaction() %d \n", errno);
		exit (1);
	}

	action . sa_handler = gestionnaire;
	sigemptyset (& (action . sa_mask));
	action . sa_flags = SA_RESTART;
	if (sigaction (SIGTERM, & action, NULL) != 0) {
		fprintf (stderr, "Erreur sigaction() %d \n", errno);
		exit (1);
	}

	fprintf (stdout, "PID = %u\n", getpid());
	fflush (stdout);

	while (1)
		pause();

	return (0);
}	
