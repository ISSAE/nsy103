
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void
gestionnaire (int numero) {
  fprintf (stdout, "\n%u a recu le signal %d (%s)\n",
	   getpid (), numero, sys_siglist[numero]);
}


int
main (void) {
  int i;

  for (i = 1; i < NSIG; i++) {
    printf("tantative association de %d (%s) au gestionnaire\n",i,sys_siglist[i]);
    if (signal (i, gestionnaire) == SIG_ERR)
      fprintf (stderr, "Signal %d non capturé\n", i);
  }
  while (1) {
    pause ();
  }
}
