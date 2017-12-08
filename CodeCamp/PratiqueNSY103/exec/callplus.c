#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char **argv) {
    int x;
    int i;
    printf("pid=%d,ppid=%d\n", getpid(), getppid());
    for (i=0; i<5; i++) {
    if (fork()==0) {
            printf("Avant appel apres fork pid=%d,ppid=%d\n", getpid(), getppid());
            execl("/home/pascalfares/nsy103/PratiqueNSY103/exec/plus","I catch you","3","4", NULL);
        }
   }
   wait(&x);
   printf("Mom fils est mort!!! %d",x);

}
