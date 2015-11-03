#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char **argv) {
int status;
printf ("P: Création d'un fils\n");
int ret=fork();
/*******************/
/* Partie du fils  */
if (ret==0) {
   execl("/home/pascalfares/add","addhehe","3","4", NULL);
   
   printf("F: Ne viendra jamais ici\n");
}
/*****************/
printf ("P,F: %d Attendre le fils\n", getpid());
wait(&status);
printf("P,F:status = %d\n",status);
}

