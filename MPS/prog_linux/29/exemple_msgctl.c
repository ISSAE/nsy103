	#include <stdio.h>
	#include <string.h>
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/msg.h>

	int
main (int argc, char * argv [])
{
	key_t     key;
	int       file;
	
	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s fichier_clé \n",
				argv [0]);
		exit (1);
	}
	if ((key = ftok (argv [1], 0)) == -1) {
		perror ("ftok");
		exit (1);
	}
	if ((file = msgget (key, 0)) == -1)
		exit (0);
	msgctl (file, IPC_RMID, NULL);
	return (0);
}
