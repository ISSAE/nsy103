#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

pid_t pid;
void onalarm () {
    printf("....Handler onalarm %d Je vais tuer %d\n", SIGKILL,pid);
    kill (pid, SIGKILL);
    exit (1);
}
int main() {

    int status;
    pid = fork();
    if (pid == -1) printf ("erreur creation de processus");
else if (pid == 0) { 
     printf ("Je suis le fils, %d %d %d En boucle infini sauf! \n", pid, getpid(),getppid());
     getchar();
     
     for(;;) printf(".");
     exit(6); 
     }
else {
    printf ("Je suis le père, %d %d %d\n", pid, getpid(), getppid());
    signal (SIGALRM, onalarm);
    alarm(1);
    wait (&status);
    }
}


