#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>


pthread_mutex_t m;
pthread_mutex_t print;
pthread_cond_t cond;
int condition = 0;

void *
ecoute (void *beurk)
{
  pthread_mutex_lock (&m);
  while (!condition)
    pthread_cond_wait (&cond, &m);
  pthread_mutex_unlock (&m);

  pthread_mutex_lock (&print);
  printf (" Condition realisee\n");
  pthread_mutex_unlock (&print);
}

main ()
{
  pthread_t lathread;
  pthread_mutex_init(&m, NULL);
  pthread_mutex_init(&print, NULL);
  
  pthread_cond_init(&cond, NULL);
  
  pthread_create (&lathread, NULL, ecoute, NULL);
  sleep (5);
  pthread_mutex_lock (&m);
  condition = 1;
  pthread_mutex_unlock (&m);
  pthread_cond_signal (&cond);
}
