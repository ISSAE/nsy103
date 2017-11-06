#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {

int res;

printf("Le père %d \n", getpid());

if (fork()==0) {
  execl("/home/cnamliban/mesgit/nsy103/GCC/lesProcessus/Recouvrement/calc", "./calc", "2", "toto", "titi", 0);
  printf("Je ne viens jamais ici \n");
} else {
  printf("Le père attend son fils \n");
  wait(&res);
  printf("Le fils c'est terminé avec ;e code %d\n", res);
}
}
