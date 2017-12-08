/******************************************
/* Exemple creation et join de thread
/* Author (c) Pascal Fares
/* Under LGPL 3
/* https://www.gnu.org/licenses/lgpl.html
/******************************************/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

/**
 * Tableau des id de thread créés
 */
pthread_t tid[2];
int ret1,ret2;

//void* equivalent a ANY
void* doSomeThing(void *arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();
    int *param = (int *)arg;

    printf("\n thread avant traitement %d\n", *param);
    for(i=0; i<(0xFFFFFFFF);i++);

    if(pthread_equal(id,tid[0]))
    {
        printf("\n premier thread terminé\n");
        ret1  = 100;
        pthread_exit(&ret1);
    }
    else
    {
        printf("\n Second thread terminé\n");
        ret2  = 200;
        pthread_exit(&ret2);
    }

    return NULL;
}

int main(void)
{
    int i = 0;  
    int err;
    int *ptr[2];
    
    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, &i);
        if (err != 0)
            printf("\nPas réussi à créer le thread :[%s]", strerror(err));
        else
            printf("\n création de thread ok %ld\n",tid[i]);

        i++;
    }

    pthread_join(tid[0], (void**)&(ptr[0]));
    pthread_join(tid[1], (void**)&(ptr[1]));

    printf("\n resultat premier thread [%d]\n", *ptr[0]);
    printf("\n resultat second  thread [%d]\n", *ptr[1]);

    return 0;
}
