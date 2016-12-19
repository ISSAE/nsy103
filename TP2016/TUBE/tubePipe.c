#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

int main() {
    int p[2];
    char buffer[10];
    int nbc;
    pipe(p);
    
    if (fork() == 0) {
        //Je suis le fils
        close(p[1]); //Suprime le tube output de chez le fils
        
        //close(0); //suprime la référence vers le 0
        //dup(p[0]);
        
        dup2(p[0],0);
        
        //Lire le input du tube
        nbc=read(0, buffer,10);
        
        //Ecrire dans le standard output
        write(1, buffer, nbc);
        
        exit(0);
        
    } else {
        //je suis le père
        close (p[0]); //suprime le tube input chez le père
        
        dup2(p[1],1);
        //Lire le standard input
        //read(0,buffer,10);
        printf("%d\n", getpid());
        
        //write(p[1], buffer, strlen(buffer));       
        
    }
}

