#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

pid_t pid;

void onalarm (int x) { 
       printf("Handler onalarm %d\n",x);
       kill (pid, SIGKILL);
       exit (0);
}

int main() {

pid = fork();
if (pid == -1)
     printf ("erreur creation de processus");
else
if (pid == 0) {
      printf ("valeur du fork, %d", pid);
      printf (" je suis le fils, mon pid est %d\n", getpid());
      for(;;)
           printf("je boucle !!!! \n");
      exit(0); 
}
else {
    printf (" Je suis le père valeur du fork, %d", pid);
    signal (SIGALRM, onalarm);
    alarm(5);
    wait (NULL); 
 }
}
