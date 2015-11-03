#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int gx;

/*
Je suis le père id est 3216 pour père est 2570 mon fils est 3217
P : x=20, gx=200, &x=0x7ffe3509e860, &gx=0x601064
Je suis le fils id est 3217 pour père est 3216 mon fils est 0
F : x=30, gx=300, &x=0x7ffe3509e860, &gx=0x601064

comment aux même adresses il y a des valeurs différentes, voir gestion mémoire.
*/
int main(int argc, char **argv){
    
    int x;
    printf("Mon id est %d pour père est %d\n", getpid(), getppid());

    x=10;gx=100;
    int ret=fork();

    if (ret>0) {
          printf("Je suis le père id est %d pour père est %d mon fils est %d\n", getpid(), getppid(), ret);
          x=30;gx=300;
          while (1)
          printf("P %d: x=%d, gx=%d, &x=%p, &gx=%p\n", getpid(), x, gx, &x, &gx);
    } else if (ret ==0) {
             printf("Je suis le fils id est %d pour père est %d mon fils est %d\n", getpid(), getppid(), ret);
          x=20;gx=200;
          while(1)
          printf("F %d: x=%d, gx=%d, &x=%p, &gx=%p\n", getpid(), x, gx, &x, &gx);    
    } else {
       printf("===ERROR===");
    }

    return (0);
}

