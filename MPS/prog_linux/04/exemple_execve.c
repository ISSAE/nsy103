
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <errno.h>

	extern char ** environ;	

	int
main (void)
{
	char * argv [] = {"sh", "-c", "echo $SHLVL", NULL };
	
	fprintf (stdout, "Je lance /bin/sh -c \"echo $SHLVL\" :\n");

	execve ("/bin/sh", argv, environ);

	fprintf (stdout, "Raté : erreur = %d\n", errno);
	return (0);
}
