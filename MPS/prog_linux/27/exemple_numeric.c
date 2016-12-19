	#include <locale.h>
	#include <stdio.h>

	int
main (int argc, char * argv [])
{
	double d = 2000.01;
	
	setlocale (LC_ALL, "");

	fprintf (stdout, "%.2f\n", d);
	return (0);
}
