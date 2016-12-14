#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>



int main(int argc, char **argv, char **envp) {
    int i;
    int p;
    printf("LANCE BOUCLE : mon id =%u mon pere id est %u\n", getpid(), getppid());

    p=fork();

    if (p==0) {
         execlp("./boucle", "boucle", NULL);
    } else {
         while (1) {
             printf(".");
         }
    }
    
    
}
