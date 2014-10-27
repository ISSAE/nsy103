
	#include <stdio.h>

	typedef enum {
		un, deux, trois
	} enum_t;

	int
main (void)
{
	fprintf (stdout, "sizeof (enum_t) = %d\n", sizeof (enum_t));

	return (0);
}
