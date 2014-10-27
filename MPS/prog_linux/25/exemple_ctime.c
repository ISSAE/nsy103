	#include <stdio.h>
	#include <time.h>

	int
main (void)
{
	time_t t;
	t = time (NULL);
	fprintf (stdout, "%s", ctime (& t));
	return (0);
}
