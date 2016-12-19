        
	#define _GNU_SOURCE

	#include <stdio.h>
        #include <stdlib.h>
        #include <signal.h>
        #include <string.h>

        int
main (void)
{
        int i;

	fprintf (stderr, "strsignal() :\n");
        for (i = 1; i < NSIG; i ++)
                fprintf (stderr, "%s\n", strsignal (i));

	fprintf (stderr, "\nsys_siglist[] : \n");
        for (i = 1; i < NSIG; i ++)
                fprintf (stderr, "%d : %s\n", i, sys_siglist [i]);

        return (0);
}

