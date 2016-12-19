
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <signal.h>
	#include <errno.h>
	#include <sys/time.h>
	#include <sys/wait.h>

	static int	temporisation_ecoulee;

	void
gestionnaire_sigalrm (int inutile)
{
	temporisation_ecoulee = 1;
}

	int
sommeil_precis (long nb_secondes, long nb_microsecondes)
{
	struct sigaction action;
	struct sigaction ancienne_action;
	sigset_t	 masque_sigalrm;
 	sigset_t	 ancien_masque;
	int		 sigalrm_dans_ancien_masque = 0;
	struct itimerval ancien_timer;
	struct itimerval nouveau_timer;
	int		 retour = 0;
	
	/* Préparation du timer */
	timerclear (& (nouveau_timer . it_interval));
	nouveau_timer . it_value . tv_sec = nb_secondes;
	nouveau_timer . it_value . tv_usec = nb_microsecondes;

	/* Installation du gestionnaire d'alarme */
	action . sa_handler = gestionnaire_sigalrm;
	sigemptyset (& (action . sa_mask));
	action . sa_flags = SA_RESTART;
	if (sigaction (SIGALRM, & action, & ancienne_action) != 0)
		return (-1);

	/* Blocage de SIGALRM avec memorisation du masque en cours */
	sigemptyset (& masque_sigalrm);
 	sigaddset (& masque_sigalrm, SIGALRM); 
	if (sigprocmask (SIG_BLOCK, & masque_sigalrm, & ancien_masque) != 0) {
		retour = -1;
		goto reinstallation_ancien_gestionnaire;
	}
 	if (sigismember (& ancien_masque, SIGALRM)) {
		sigalrm_dans_ancien_masque = 1;
		sigdelset (& ancien_masque, SIGALRM);
	}
	/* Initialisation de la variable globale */
	temporisation_ecoulee = 0;

	/* Sauvegarde de l'ancien timer */
	if (getitimer (ITIMER_REAL, & ancien_timer) != 0) {
		retour = -1;
		goto restitution_ancien_masque;
	}

	/* Déclenchement du nouveau timer */
	if (setitimer (ITIMER_REAL, & nouveau_timer, NULL) != 0) {
		retour = -1;
		goto restitution_ancien_timer;
	}

	/* Boucle d'attente de la fin du sommeil */	
	while (! temporisation_ecoulee) {
 		if ((sigsuspend (& ancien_masque) != 0) &&
		    (errno != EINTR)) {
			retour = -1;
			break;
		}
 	} 
	
restitution_ancien_timer:

	if (setitimer (ITIMER_REAL, & ancien_timer, NULL) != 0)
		retour = -1;

restitution_ancien_masque :

	if (sigalrm_dans_ancien_masque) {
		sigaddset (& ancien_masque, SIGALRM);
	}
	if (sigprocmask (SIG_SETMASK, & ancien_masque, NULL) != 0)
		retour = -1;

reinstallation_ancien_gestionnaire :
	
	if (sigaction (SIGALRM, & ancienne_action, NULL) != 0)
		retour = -1;

	return (retour);
}


	void
gestionnaire_sigusr1 (int inutile)
{
}

	int
main (void)
{
	pid_t		 pid;
	struct sigaction action;
	int		 i;

	if ((pid = fork ()) < 0) {
		fprintf (stderr, "Erreur dans fork\n");
		exit (1);
	}
	
	action . sa_handler = gestionnaire_sigusr1;
	sigemptyset (& (action . sa_mask));
	action . sa_flags = SA_RESTART;

	if (sigaction (SIGUSR1, & action, NULL) != 0) {
		fprintf (stderr, "Erreur dans sigaction\n");
		exit (1);
	}

	if (pid == 0) {
		system ("date +\"Fils : %H:%M:%S\"");
		if (sommeil_precis (60, 0) != 0) {
			fprintf (stderr, "Erreur dans sommeil_precis\n");
			exit (1);
		}
		system ("date +\"Fils : %H:%M:%S\"");
	} else {
		sommeil_precis (2, 0);
		system ("date +\"Père : %H:%M:%S\"");
		for (i = 0; i < 3000; i ++) {
			sommeil_precis (0, 20000); /* 1/50 de seconde */
			kill (pid, SIGUSR1);
		}
		system ("date +\"Père : %H:%M:%S\"");
		waitpid (pid, NULL, 0);
	}
	return (0);
}
