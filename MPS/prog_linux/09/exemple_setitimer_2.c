
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <signal.h>
	#include <sys/time.h>
	#include <sys/wait.h>


	unsigned long int	mode_utilisateur;
	unsigned long int	mode_utilisateur_et_noyau;

	void	gestionnaire_signaux	(int numero);
	void	fin_du_suivi		(void);
	void	action_a_mesurer	(void);
	
	int
main (void)
{
	struct sigaction action;
	struct itimerval timer;
	
	/* Préparation du timer */
	timer . it_value . tv_sec = 0;
	timer . it_value . tv_usec = 10000; /* 1/100 s. */
	timer . it_interval . tv_sec = 0;
	timer . it_interval . tv_usec = 10000; /* 1/100 s. */

	/* Installation du gestionnaire de signaux */
	action . sa_handler = gestionnaire_signaux;
	sigemptyset (& (action . sa_mask));
	action . sa_flags = SA_RESTART;
	if ((sigaction (SIGVTALRM, & action, NULL) != 0)
	 || (sigaction (SIGPROF, & action, NULL) != 0)) {
		fprintf (stderr, "Erreur dans sigaction\n");
		return (-1);
	}

	/* Déclenchement des nouveaux timers */
	if ((setitimer (ITIMER_VIRTUAL, & timer, NULL) != 0)
	 || (setitimer (ITIMER_PROF, & timer, NULL) != 0)) {
		fprintf (stderr, "Erreur dans setitimer\n");
		return (-1);
	}

	/* Installation de la routine de sortie du programme */
	if (atexit (fin_du_suivi) != 0) {
		fprintf (stderr, "Erreur dans atexit\n");
		return (-1);
	}

	/* Appel de la routine de travail effectif du processus */
	action_a_mesurer ();	

	return (0);
}

	void
gestionnaire_signaux (int numero)
{
	switch (numero) {
		case SIGVTALRM :
			mode_utilisateur ++;
			break;
		case SIGPROF :
			mode_utilisateur_et_noyau ++;
			break;
	}
}

	void
fin_du_suivi (void)
{
	sigset_t	masque;
	
	/* Blocage des signaux pour éviter une modification */
	/* des compteurs en cours de lecture.               */
	sigemptyset (& masque);
	sigaddset (& masque, SIGVTALRM);
	sigaddset (& masque, SIGPROF);
	sigprocmask (SIG_BLOCK, & masque, NULL);

	/* Comme on quitte à présent le programme, on ne 
	 * restaure pas l'ancien comportement des timers,
	 * mais il faudrait le faire dans une routine de
	 * bibliothèque.
	 */
	
	fprintf (stdout, "Temps passé en mode utilisateur : %ld/100 s.\n",
			mode_utilisateur);
	fprintf (stdout, "Temps passé en mode noyau : %ld/100 s.\n",
			mode_utilisateur_et_noyau - mode_utilisateur);
}

	void
action_a_mesurer (void)
{
	int i, j;
	FILE * fp1, * fp2;
	double x;
	
	x = 0.0;
	for (i = 0; i < 10000; i ++)
		for (j = 0; j < 10000; j ++) 
			x += i * j;

	for (i = 0; i < 500; i ++) {
		if ((fp1 = fopen ("exemple_setitimer_2", "r")) != NULL) {
			if ((fp2 = fopen ("/dev/null", "w")) != NULL) {
				while (fread (& j, sizeof (int), 1, fp1) == 1)
					fwrite (& j, sizeof (int), 1, fp2);
				fclose (fp2);
			}
			fclose (fp1);
		}
	}
}

