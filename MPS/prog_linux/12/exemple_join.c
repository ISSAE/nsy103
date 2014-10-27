	#include <pthread.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>

	void *
fn_thread (void * inutile)
{
	char	chaine [128];
	int	i = 0;
	fprintf (stdout, "Thread : entrez un nombre :");
	while (fgets (chaine, 128, stdin) != NULL)
		if (sscanf (chaine, "%d", & i) != 1)
			fprintf (stdout, "un nombre svp :");
		else
			break;
	pthread_exit ((void *) i);
}

	int
main (void)
{
	int       i;
	int       ret;
	pthread_t thread;
	void *    retour;

	if ((ret = pthread_create (& thread, NULL, fn_thread, NULL)) != 0) {
		fprintf (stderr, "%s\n", strerror (ret));	
		exit (1);
	}
	pthread_join (thread , & retour);
	if (retour!= PTHREAD_CANCELED) {
		i = (int) retour;
		fprintf (stdout, "main : valeur lue = %d\n", i);
	}
	return (0);
}
