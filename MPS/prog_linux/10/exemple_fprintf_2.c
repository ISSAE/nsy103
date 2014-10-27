	#include <stdio.h>

	int
main (void)
{
	int	d;

	fprintf (stdout, "| %%6d  | %%+6d | %%-6d | %%-+6d| %% 6d | %%06d |\n");
	fprintf (stdout, "+------+------+------+------+------+------+\n");
	d = 0;
	fprintf (stdout, "|%6d|%+6d|%-6d|%-+6d|% 6d|%06d|\n", d, d, d, d, d, d);
	d = 1;
	fprintf (stdout, "|%6d|%+6d|%-6d|%-+6d|% 6d|%06d|\n", d, d, d, d, d, d);
	d = -2;
	fprintf (stdout, "|%6d|%+6d|%-6d|%-+6d|% 6d|%06d|\n", d, d, d, d, d, d);
	d = 100;
	fprintf (stdout, "|%6d|%+6d|%-6d|%-+6d|% 6d|%06d|\n", d, d, d, d, d, d);
	d = 1000;
	fprintf (stdout, "|%6d|%+6d|%-6d|%-+6d|% 6d|%06d|\n", d, d, d, d, d, d);
	d = 10000;
	fprintf (stdout, "|%6d|%+6d|%-6d|%-+6d|% 6d|%06d|\n", d, d, d, d, d, d);
	d = 100000;
	fprintf (stdout, "|%6d|%+6d|%-6d|%-+6d|% 6d|%06d|\n", d, d, d, d, d, d);
	return (0);
}


