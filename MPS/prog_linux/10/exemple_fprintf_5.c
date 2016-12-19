	#include <stdio.h>
	#include <time.h>

	int
main (void)
{
	int	i;

	char	* format [2] =

	{ "La date est %3$02d/%2$02d/%1$02d\n",
	  "Today is %1$02d %2$02d %3$02d\n" };

	time_t	timer;
	struct tm * date;

	time (& timer);
	date = localtime (& timer);

	for (i = 0; i < 2; i ++)

		fprintf (stdout, format [i], 
				date  -> tm_year % 100,
				date  -> tm_mon + 1,
				date  -> tm_mday);


	return (0);
}


