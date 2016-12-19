	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <pthread.h>


	pthread_cond_t	condition_alarme
			= PTHREAD_COND_INITIALIZER;
	pthread_mutex_t	mutex_alarme
			= PTHREAD_MUTEX_INITIALIZER;


	static void *   thread_temperature (void * inutile);
	static void *   thread_alarme      (void * inutile);
	static int	aleatoire          (int    maximum);

	int
main (void)
{
	pthread_t thr;
	pthread_create (& thr, NULL, thread_temperature, NULL);
	pthread_create (& thr, NULL, thread_alarme,      NULL);
	pthread_exit (NULL);
}

	static void *
thread_temperature (void * inutile)
{
	int	temperature = 20;
	while (1) {
		temperature += aleatoire (5) - 2;
		fprintf (stdout, "Température : %d\n", temperature);
		if ((temperature < 16) || (temperature > 24)) {
			pthread_mutex_lock (& mutex_alarme);
			pthread_cond_signal (& condition_alarme);
			pthread_mutex_unlock (& mutex_alarme);
		}	
		sleep (1);
	}	
	return (NULL);
}

	static void *
thread_alarme (void * inutile)
{
	while (1) {
		pthread_mutex_lock (& mutex_alarme);
		pthread_cond_wait (& condition_alarme,
				   & mutex_alarme);
		pthread_mutex_unlock (& mutex_alarme);
		fprintf (stdout, "ALARME\n");
	}
	return (NULL);
}

	static int
aleatoire (int maximum)
{
	double d;
	d = (double) maximum * rand ();
	d = d / (RAND_MAX + 1.0);
	return ((int) d);
}
