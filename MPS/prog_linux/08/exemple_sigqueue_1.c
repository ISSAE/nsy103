	#include <signal.h>
	#include <stdio.h>
	#include <unistd.h>

	int	signaux_arrives [10];
	int	valeur_arrivee  [10];
	int	nb_signaux = 0;
	
	void
gestionnaire_signal_temps_reel (int numero, siginfo_t * info, void * inutile)
{
	signaux_arrives [nb_signaux] = numero - SIGRTMIN;
	valeur_arrivee  [nb_signaux] = info -> si_value . sival_int;
	nb_signaux ++;
}

	void
envoie_signal_temps_reel (int numero, int valeur)
{
	union sigval valeur_sig;

	fprintf (stdout, "Envoi signal SIRTMIN+%d, valeur %d\n",
	                  numero, valeur);
	valeur_sig . sival_int = valeur;
	if (sigqueue (getpid(), numero + SIGRTMIN, valeur_sig) < 0) {
		perror ("sigqueue");
		exit (1);
	}
}

	int
main (void)
{
	struct sigaction action;
	sigset_t         ensemble;
	int              i;

	fprintf (stdout, "Installation gestionnaires de signaux\n");
	action . sa_sigaction = gestionnaire_signal_temps_reel;
	sigemptyset (& action . sa_mask);
	action . sa_flags = SA_SIGINFO;
	if ((sigaction (SIGRTMIN + 1, & action, NULL) < 0)
	 || (sigaction (SIGRTMIN + 2, & action, NULL) < 0)
	 || (sigaction (SIGRTMIN + 3, & action, NULL) < 0)) {
		perror ("sigaction");
		exit (1);
	}
	
	fprintf (stdout, "Blocage de tous les signaux\n");
	sigfillset (& ensemble);
	sigprocmask (SIG_BLOCK, & ensemble, NULL);

	envoie_signal_temps_reel (1, 0);
	envoie_signal_temps_reel (2, 1);
	envoie_signal_temps_reel (3, 2);
	envoie_signal_temps_reel (1, 3);
	envoie_signal_temps_reel (2, 4);
	envoie_signal_temps_reel (3, 5);
	envoie_signal_temps_reel (3, 6);
	envoie_signal_temps_reel (2, 7);
	envoie_signal_temps_reel (1, 8);
	envoie_signal_temps_reel (3, 9);
	
	fprintf (stdout, "Déblocage de tous les signaux\n");
	sigfillset (& ensemble);
	sigprocmask (SIG_UNBLOCK, & ensemble, NULL);

	fprintf (stdout, "Affichage des résultats\n");
	for (i = 0; i < nb_signaux; i ++)
		fprintf (stdout, "Signal SIGRTMIN+%d, valeur %d\n",
                        signaux_arrives [i], valeur_arrivee [i]);

	fprintf (stdout, "Fin du programme\n");
	return (0);
}

