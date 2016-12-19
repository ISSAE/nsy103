#include <stdio.h>

#include <stdlib.h>

#include <pthread.h> 

void *fonction_thread (void * arg) {

  int i; 

  for (i = 0 ; i < 5 ; i++) {

    printf ("%s thread: %d\n", (char*)arg, i);

    usleep(10);

  }

  pthread_exit(0);

} 

int main (void) {

  pthread_t th1, th2;

  void *ret; 

  if (pthread_create (&th1, NULL, fonction_thread, "Premier")      < 0) {

    perror("premier (pthread_create)");

    exit (-1);

  } 

  if (pthread_create (&th2, NULL, fonction_thread,

		      "Second") <  0) {

    perror("second (pthread_create)");

    exit (-1);

  } 
  (void)pthread_join (th1, &ret);

  (void)pthread_join (th2, &ret);

  return 0;

}
