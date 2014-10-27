
	#include <stdio.h>
	#include <syslog.h>

	int
main (int argc, char * argv [])
{
	int 	i;

	openlog (argv [0], LOG_PID, LOG_USER);

	for (i = 1; i < argc; i ++)
		syslog (LOG_INFO, argv [i]);

	closelog ();

	return (0);
}
