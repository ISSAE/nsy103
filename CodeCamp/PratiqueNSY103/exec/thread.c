#include <stdio.h>
#include <pthread.h>

pthread_t pthread_id[3];

void* f_thread(void *i) {
     int *x= (int *)i;
     printf ("je suis le thread %d.%ld\n param était %d\n\n",getpid(), pthread_self(),*x); 
}

main() {
  int i;
  for (i=0; i<3; i++) {
        if (pthread_create(&(pthread_id[i]), NULL, f_thread,&i) == -1)
     fprintf(stderr, "erreur de creation pthread numero %d\n", i);
  }
     printf ("je suis la thread initiale %d.%ld\n",getpid(), pthread_self()); 

   pthread_join(pthread_id[0], NULL);
   pthread_join(pthread_id[1], NULL);
   pthread_join(pthread_id[2], NULL);
}
