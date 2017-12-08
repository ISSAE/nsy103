#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NB_THREADS 2

void * fn_thread(void * numero);

static int compteur = 0;

int
main(void) {

    pthread_t thread [NB_THREADS];
    int i;
    int ret;

    for (i = 0; i < NB_THREADS; i++)
        if ((ret = pthread_create(& thread [i],
                NULL,
                fn_thread,
                (void *) (intptr_t) i)) != 0) {
            fprintf(stderr, "%s", strerror(ret));
            exit(1);
        }

    while (1) {
        fprintf(stdout, "main : compteur = %d\n", compteur);
        sleep(1);
    }
    for (i = 0; i < NB_THREADS; i++)
        pthread_join(thread [i], NULL);

    return (0);
}

void *
fn_thread(void * num) {
    int numero = (int) (intptr_t) num;
    while (1) {
        sleep((numero+1));
        compteur++;
        fprintf(stdout, "Thread %d : compteur = %d\n",
                numero, compteur);
    }
    pthread_exit(NULL);
}
