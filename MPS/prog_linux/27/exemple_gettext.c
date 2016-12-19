	#include <libintl.h>
	#include <stdio.h>

	int
main (void)
{
	textdomain ("exemple_gettext");
	bindtextdomain ("exemple_gettext", "/usr/share/locale");

	fprintf (stdout, gettext ("This is the first string in the first set\n"));
	fprintf (stdout, gettext ("and here is the second string in the first set.\n"));
	fprintf (stdout, gettext ("Now let's have a look at the 1st string in 2nd set,\n"));
	fprintf (stdout, gettext ("and finaly the second string in the second set.\n"));
	return (0);
}

