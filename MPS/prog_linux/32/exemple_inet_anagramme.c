	#define _GNU_SOURCE
	#include <ctype.h>
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>

	int
main (void)	
{
	char chaine [256];
	int  n;
	
	while (1) {
		if ((n = read (STDIN_FILENO, chaine, 256)) <= 1)
			break;
		while (isspace (chaine [n - 1]))
			n --;
		chaine [n] = '\0';
		strfry (chaine);
		write (STDOUT_FILENO, chaine, n);
	}
	return (0);
}

