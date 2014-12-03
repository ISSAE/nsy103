#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

pid_t pid;
onalarm () {
    printf("Handler onalarm %d\n", SIGKILL);
    kill (pid, SIGKILL);
    exit (1);
}
main() {

    int status;
    pid = fork();
    if (pid == -1) printf ("erreur creation de processus");
else if (pid == 0) { 
     printf ("Je suis le fils, %d %d %d \n", pid, getpid(),getppid());
     for(;;) printf("..je boucle !!!! ");
     exit(6); 
     }
else {
    printf ("Je suis le père, %d %d %d\n", pid, getpid(), getppid());
    signal (SIGALRM, onalarm);
    alarm(1);
    wait (&status);
    }
}


