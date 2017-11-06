#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


main () {

    int i;

    int pid,ppid;

    int resFork;


   printf("Avant l'appel de fork mon id est %d mon père est %d\n", getpid(), getppid());

   resFork = fork();

   if (resFork == 0) {
          printf("\nCAS VRAI : Dans le cas ou resFork est %d éagl a 0 mon id est %d père est %d\n", resFork, getpid(), getppid());
   } else {
        printf("\nCAS FAUX: Dans le cas ou resFork est %d n'est pas 0 mon id est %d pere est %d\n", resFork, getpid(), getppid());
   }

}
