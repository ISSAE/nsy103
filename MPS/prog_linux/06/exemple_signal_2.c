
	#define _XOPEN_SOURCE

	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

	#include <signal.h>

	void
gestionnaire (int numero)
{
	fprintf (stdout, "\n%u a reçu le signal %d\n", getpid (), numero);
}

	int
main (void)
{
	int i;

	for (i = 1; i < _NSIG; i ++)
		if (signal (i, gestionnaire) == SIG_ERR)
			fprintf (stderr, "%u ne peut capturer le signal %d\n",
				getpid(), i);
	while (1) {
		pause();
	}
}

	
