
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <signal.h>
	#include <sys/time.h>
	#include <sys/wait.h>


	void	action_a_mesurer	(void);
	
	int
main (void)
{
	action_a_mesurer ();	

	return (0);
}

	void
action_a_mesurer (void)
{
	int i, j;
	FILE * fp1, * fp2;
	double x;
		
	x = 0.0;
	for (i = 0; i < 10000; i ++)
		for (j = 0; j < 10000; j ++)
			x += i * j;

	for (i = 0; i < 500; i ++) {
		if ((fp1 = fopen ("exemple_setitimer_2", "r")) != NULL) {
			if ((fp2 = fopen ("/dev/null", "w")) != NULL) {
				while (fread (& j, sizeof (int), 1, fp1) == 1)
					fwrite (& j, sizeof (int), 1, fp2);
				fclose (fp2);
			}
			fclose (fp1);
		}
	}
}

