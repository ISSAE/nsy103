#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


main () {

    int i;

    int pid,ppid;

    int resFork;

    int x=100;
   printf("PRINCIPAL : %d <- %d\n", getpid(), getppid());

   resFork = fork();

   if (resFork == 0) {
          x=10;
          printf("\nFILS : fork=%d %d <- %d x=%d\n", resFork, getpid(), getppid(),x);
          //sleep(30);
          //printf("Après sleep du fils\n");
          //sleep(10);
   } else {
        printf("\nPERE : fork=%d %d <- %d x=%d\n", resFork, getpid(), getppid(),x);
        sleep(60);
        //printf("Après sleep du père x=%d\n", x);
        //sleep(10);
   }

}
