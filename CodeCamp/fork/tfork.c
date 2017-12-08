#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    int res;
    int p,pexit;

    printf("Je suis %d mon père est %d la taille d'un it est %ld\n", getpid(), getppid(),sizeof(int));

    p = fork();

    //Combien de fois ce prinf sera executé? pourquoi?
    printf("p = %d : Je suis %d mon père est %d\n", p, getpid(), getppid());

    if (p == 0) {
        printf("Je suis le fils : Je suis %d mon père est %d\n", getpid(), getppid());
        exit(EXIT_FAILURE);
    } else {
        printf("Je suis le père : Je suis %d mon père est %d mon fils est %d\n", getpid(), getppid(), p);
        pexit=wait(&res);
        printf("Un de mes processus %d vient de se terminé avec le code de terminaison %d\n", pexit,WEXITSTATUS(res));
    }

}
