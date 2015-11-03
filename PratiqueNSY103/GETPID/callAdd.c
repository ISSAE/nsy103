#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char **argv) {
int status;
printf ("Création d'un fils\n");
int ret=fork();
/*******************/
/* Partie du fils  */
if (ret==0) {
   execl("/home/pascalfares/add","addhehe","3","4", NULL);
   printf("Ne viendra jamais ici\n");
}
/*****************/
printf ("Attendre le fils\n");
wait(&status);
printf("status = %d\n",status);
}

