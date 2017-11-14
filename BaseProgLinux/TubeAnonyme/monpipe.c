#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char**argv) {
    int p[2];
    char buffer[10];
    int nbc;
    pipe(p);
    int status;
    
    if (fork() == 0) {
        //Le premier fils = le première commande
        dup2(p[1],1);
        execlp(argv[1], argv[1], NULL);
        //argv[2]=NULL, execvp(argv[1],argv+1);
        exit(1);
    }
    
    if (fork() == 0) {
        //Le premier fils = le première commande
        dup2(p[0],0);
        execlp(argv[2], argv[2], NULL);
        //execvp(argv[2],argv+2);
        exit(1);
    }
    wait(&status);
    wait(&status);
    printf("Le lanceeur est fini\n");
    exit(0);
}
    
    
