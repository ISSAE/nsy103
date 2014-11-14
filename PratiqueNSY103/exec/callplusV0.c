#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char **argv) {
    printf("DANS CALL pid=%d,ppid=%d\n", getpid(), getppid());
   execl("/home/pascalfares/nsy103/PratiqueNSY103/exec/plus","Plus","3","4", NULL);
   
   printf("Ce tres grave pas normal !!!");

}
