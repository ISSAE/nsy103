	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

	void
syntaxe (char * nom)
{
	fprintf (stderr, "Syntaxe %s chemin commande...\n", nom);
	exit (1);
}

	int
main (int argc, char * argv [])
{
	if (argc < 3)
		syntaxe (argv [0]);
	if (chdir (argv [1]) != 0){
		perror ("chdir");
		exit (1);
	}
	if (chroot (argv [1]) != 0) {
		perror ("chroot");
		exit (1);
	}
	if (seteuid (getuid ()) < 0) {
		perror ("seteuid");
		exit (1);
	}
	execvp (argv [2], argv + 2);
	perror ("execvp");
	return (1);
}
 
