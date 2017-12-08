#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i,j;
    int pid;
    printf("pid du père : %d \n", getpid());
    pid = fork();
    if (pid == 0) {
        //Le fils....
        for (i = 0; i < 500; i++) {
            printf(" [1 %d : %d] ", getpid(), i);
            for (j=0; j<100; j++) {
                log(exp(10.0));
                printf("-");
            } 
            printf("\n");
        }
        exit(0);
    } 

    pid = fork();
    if (pid == 0) {
        //Un autre fils...
        for (i = 500; i < 1000; i++) {
            printf(" [2 %d : %d] ", getpid(), i);
            for (j=0; j<100; j++) {
                log(exp(10.0));
                printf(".");
            }
            printf("\n");
        }
        exit(0);
    }

}

