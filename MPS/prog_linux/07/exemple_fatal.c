
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <signal.h>


	void
gestionnaire_signal_fatal (int numero)
{
	/* Effectuer le nettoyage :			*/
	/*   Couper proprement les connexions r�seau	*/
	/*   Supprimer les fichiers de verrouillage	*/
	/*   Tuer �ventuellement les processus fils	*/

	fprintf (stdout, "\nJe fais le m�nage !\n");
	fflush (stdout);
	signal (numero, SIG_DFL);
	raise (numero);
}


	int
main ()
{
	fprintf (stdout, "mon pid est %u\n", getpid ());
	signal (SIGTERM, gestionnaire_signal_fatal);
	signal (SIGSEGV, gestionnaire_signal_fatal);
	while (1)
		pause ();
	return (0);
}


