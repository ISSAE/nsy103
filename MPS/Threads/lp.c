#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

volatile int tab[5];		// Variable partagée

void *
lire (void *arg)
{

  int i;

  for (i = 0; i != 5; i++)

    printf ("Thread lecture: tab[%d] vaut %d\n", i, tab[i]);

  pthread_exit (0);

}

void *
ecrire (void *arg)
{

  int i;

  for (i = 0; i != 5; i++)
    {

      tab[i] = 2 * i;

      printf ("%d Thread ecriture: tab[%d] vaut %d\n", getpid(), i, tab[i]);

      usleep (500000);		/* Simule un calcul complexe... */

    }

  pthread_exit (0);

}

int
main (void)
{

  pthread_t th1, th2;

  void *ret;
  fork();
  if (pthread_create (&th1, NULL, ecrire, NULL) < 0)
    {
      perror ("Thread ecrire (pthread_create)");

      exit (-1);

    }
  if (pthread_create (&th2, NULL, lire, NULL) < 0)
    {

      perror ("Thread lire (pthread_create)");

      exit (-1);

    }

  (void) pthread_join (th1, &ret);

  (void) pthread_join (th2, &ret);

}
