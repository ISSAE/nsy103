#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char **env) {

    int pid;
    int toto;


    if ((pid = fork()) == 0) {
        //Un fils
        printf("%d : %d \n", getpid(), getppid());
        //Blabla un traitement qui génère une erreur doncv on rebvoie une valeur x > 0 c'est la noeme UNIX

        exit(0x1);
    }

    if ((pid = fork()) == 0) {
        //Un autre fils
        printf("%d : %d \n", getpid(), getppid());
        //Blabla un traitement qui génère une erreur doncv on rebvoie une valeur x > 0 c'est la noeme UNIX

        exit(0);
    }
    if ((pid = fork()) == 0) {
        //encore un autre fils Un fils
        printf("%d : %d \n", getpid(), getppid());
        //Blabla un traitement qui génère une erreur doncv on rebvoie une valeur x > 0 c'est la noeme UNIX

        exit(0x123);
    }

    
    pid = wait(&toto);
    
    printf("Mon fils %d vien de se termioner avec le status %x\n", pid, toto);

    pid = wait(&toto);
    printf("Mon fils %d vien de se termioner avec le status %x\n", pid, toto);
    pid = wait(&toto);
    printf("Mon fils %d vien de se termioner avec le status %x\n", pid, toto);

}

