
	#include <stdio.h>
	#include <time.h>

	int
main (void)
{
	tzset ();
	fprintf (stdout, "tzname[0] = %s\n", tzname [0]);	
	fprintf (stdout, "tzname[1] = %s\n", tzname [1]);	
	return (0);
}
