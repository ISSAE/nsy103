#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Tableau des id de thread créés
 */
pthread_t tid[10];

sem_t sem;

int x = 0;

// void* equivalent a ANY
void *incX(void *arg) {
  unsigned int i = 0;
  int xavant = x;
  for (i = 0; i < 10000; i++) {
    x += 1;
  }
}

int main(void) {
  int i = 0;
  int err;
  int *ptr[10];
  // Lancer 10 threads, chaque thread incrémente x de 10000
  while (i < 10) {
    err = pthread_create(&(tid[i]), NULL, &incX, &i);
    if (err != 0)
      printf("\nPas réussi à créer le thread :[%s]", strerror(err));
    else
      printf("\n création de thread ok %ld\n", tid[i]);

    i++;
  }
  // attendre le fin de touts les threads
  for (i = 0; i < 10; i++) {
    pthread_join(tid[i], (void **)&(ptr[i]));
  }
  printf("valeur de x après prévu : 10*10000 réel est %d\n", x);
  return 0;
}