
	#include <fcntl.h>
	#include <stdio.h>
	#include <unistd.h>

	int
main ()
{
	int	etat;
	etat = fcntl (STDIN_FILENO, F_GETFL) & O_ACCMODE;
	fprintf (stderr, "stdin : %s\n",
		(etat == O_RDWR) ? "R/W" : (etat == O_RDONLY) ? "R" : "W");
	etat = fcntl (STDOUT_FILENO, F_GETFL) & O_ACCMODE;
	fprintf (stderr, "stdout : %s\n",
		(etat == O_RDWR) ? "R/W" : (etat == O_RDONLY) ? "R" : "W");
	etat = fcntl (STDERR_FILENO, F_GETFL) & O_ACCMODE;
	fprintf (stderr, "stderr : %s\n",
		(etat == O_RDWR) ? "R/W" : (etat == O_RDONLY) ? "R" : "W");
	return (0);
}
