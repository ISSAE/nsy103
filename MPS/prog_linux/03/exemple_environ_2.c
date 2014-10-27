
	#include <stdio.h>

	int
main (int argc, char * argv [], char * envp [])
{
	int	i = 0;

	for (i = 0; envp [i] != NULL; i ++)
		fprintf (stdout, "%d : %s\n", i, envp [i]);

	return (0);
}
