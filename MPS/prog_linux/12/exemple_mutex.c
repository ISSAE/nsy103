	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <pthread.h>



	static void *	routine_threads (void * argument);
	static	int	aleatoire	(int maximum);

	pthread_mutex_t	mutex_stdout = PTHREAD_MUTEX_INITIALIZER;

	int
main (void)
{
	int		i;
	pthread_t	thread;
	
	for (i = 0; i < 10; i ++)
		pthread_create (& thread, NULL, routine_threads, (void *) i);
	pthread_exit (NULL);
}

	static void *
routine_threads (void * argument)
{
	int numero = (int) argument;
	int nombre_iterations;
	int i;
	nombre_iterations = aleatoire (6);
	for (i = 0; i < nombre_iterations; i ++) {
		sleep (aleatoire (3));
		pthread_mutex_lock (& mutex_stdout);
		fprintf (stdout, "Le thread num�ro %d tient le mutex\n", numero);
		pthread_mutex_unlock (& mutex_stdout);
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
