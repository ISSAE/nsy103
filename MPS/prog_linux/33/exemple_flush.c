	#include <stdio.h>
	#include <termios.h>
	#include <unistd.h>

	int
main (void)
{
	struct termios terminal;
	int i;

	fprintf (stdout, "FLUSH dans 5 secondes\n");
	sleep (5);
	fprintf (stdout, "FLUSH !\n");
	if (tcgetattr (STDIN_FILENO, & terminal) == 0)
		tcsetattr (STDIN_FILENO, TCSAFLUSH, & terminal);
	while ((i = fgetc (stdin)) != EOF)
		fprintf (stdout, "%02X ", i);
	return (0);
}
