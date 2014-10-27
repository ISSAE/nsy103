	#include <stdio.h>
	#include <stdlib.h>
	#include <signal.h>
	#include <pthread.h>

	static void * thread_compteur    (void * inutile);
	static void * thread_signaux     (void * inutile);

	static int               compteur       = 0;
	static pthread_mutex_t   mutex_compteur = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t    cond_compteur  = PTHREAD_COND_INITIALIZER;

	static pthread_t	thr_signaux;
	static pthread_t	thr_compteur;
	int
main (void)
{
	pthread_create (& thr_compteur, NULL, thread_compteur, NULL);
	pthread_create (& thr_signaux,  NULL, thread_signaux,  NULL);
	pthread_exit (NULL);
}

	static void *
thread_compteur (void * inutile)
{
	sigset_t masque;
	sigfillset (& masque);
	pthread_sigmask (SIG_BLOCK, & masque, NULL);
	while (1)  {
		pthread_mutex_lock (& mutex_compteur);
		pthread_cleanup_push (pthread_mutex_unlock,
				      (void *) & mutex_compteur);
		pthread_cond_wait (& cond_compteur,
				   & mutex_compteur);
		fprintf (stdout, "Compteur : %d \n", compteur);
		if (compteur > 5)
			break;
		pthread_cleanup_pop (1); /* mutex_unlock */
	}
	pthread_cancel (thr_signaux);
	return (NULL);
}

	static void *
thread_signaux (void * inutile)
{
	sigset_t masque;
	int      numero;
	
	sigemptyset (& masque);
	sigaddset (& masque, SIGINT);
	sigaddset (& masque, SIGQUIT);
	while (1) {
		sigwait (& masque, & numero);
		pthread_mutex_lock (& mutex_compteur);	
		switch (numero) {
			case SIGINT :
				compteur ++;
				break;
			case SIGQUIT :
				compteur --;
				break;
		}
		pthread_cond_signal (& cond_compteur);
		pthread_mutex_unlock (& mutex_compteur);
	}
	return (NULL);
}
