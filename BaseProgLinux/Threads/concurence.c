#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <semaphore.h>

/**
 * Tableau des id de thread créés
 */
pthread_t tid[10];

sem_t sem;

int x=0;

//void* equivalent a ANY
void* incX(void *arg)
{
    unsigned int i = 0;
    int xavant=x;
    pthread_t id = pthread_self();

    //printf("X avant %lu %d\n", id, xavant);
    for (i=0; i< 10000; i++) {
        //printf("X ++ %d",x);
        //P(S)
        sem_wait(&sem);
        x +=1;
        sem_post(&sem);
        //V(S)
    }
    //printf("X apres %lu  normalement %d %d\n", id, x, xavant+10000);
}

int main(void)
{
    int i = 0;  
    int err;
    int *ptr[10];
    sem_init(&sem,0,1);
    while(i < 10)
    {
        err = pthread_create(&(tid[i]), NULL, &incX, &i);
        if (err != 0)
            printf("\nPas réussi à créer le thread :[%s]", strerror(err));
        //else
            //printf("\n création de thread ok %ld\n",tid[i]);

        i++;
    }

    for (i=0; i<10; i++) {
        //printf("join %lu\n",tid[i]);
         pthread_join(tid[i], (void**)&(ptr[i]));
    }
    

    printf("valeur de x après 10*10000 est %d\n",x);

    return 0;
}