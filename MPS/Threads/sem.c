#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include <semaphore.h>

static sem_t my_sem;

int the_end;

void *
thread1_process (void *arg)
{

  while (!the_end)
    {

      printf ("Je t'attend !\n");

      sem_wait (&my_sem);

    }
  printf ("OK, je sors !\n");

  pthread_exit (0);

}

void *
thread2_process (void *arg)
{

  register int i;
  for (i = 0; i < 5; i++)
    {

      printf ("J'arrive %d !\n", i);

      sem_post (&my_sem);

      sleep (1);

    }
  the_end = 1;

  sem_post (&my_sem);		/* Pour debloquer le dernier sem_wait */

  pthread_exit (0);

}

int
main (void)
{

  pthread_t th1, th2;

  void *ret;
  sem_init (&my_sem, 0, 0);

  if (pthread_create (&th1, NULL, thread1_process, NULL) < 0)
    {

      fprintf (stderr, "pthread_create error for thread 1\n");

      exit (-1);

    }

  if (pthread_create (&th2, NULL, thread2_process, NULL) < 0)
    {

      fprintf (stderr, "pthread_create error for thread 2\n");

      exit (-1);

    }

  (void) pthread_join (th1, &ret);

  (void) pthread_join (th2, &ret);

  return 0;

}
