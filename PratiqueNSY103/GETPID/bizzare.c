#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (int argc, char **argv) {
int status;
int i;
printf ("P: Création d'un fils\n");
int ret=fork();
/*******************/
/* Partie du fils  */
if (ret==0) {
   /* execl("/home/pascalfares/add","addhehe","3","4", NULL);
   */
   for (i=0;i<100;i++) { 
      printf("F ");
   }
   exit(0);
}
/*****************/
printf ("P: %d filsid=%d Attendre le fils\n", getpid(), ret);
wait(&status);
printf("P:status = %d\n",status);
}

