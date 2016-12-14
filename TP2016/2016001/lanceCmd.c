#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[], char **env){
    
    char **myargv;
    int i;
    int pid,pidended;
    int status;

    /**
    myargv=(char **)malloc(argc * sizeof(char *));
    
    for (i=1;i<argc;i++) {
       myargv[i-1]=argv[i]; 
       printf("%s %d",myargv[i-1], i-1);
    }
    myargv[argc-1]=NULL;
    printf("%s %d\n",myargv[argc-1], argc-1);

    // argv+1 remplace tout ceci et est suffisant
    */

    if ((pid =fork()) == 0) {
        //Je suis le fils
        //execve (argv[1], myargv, env);
        printf("chez le fils... avant execvp %d", getpid());
        execvp (argv[1], argv+1);
        perror("\n--------------si ici pas OK---\n");
        exit(1);
    }
    /** attendre la fin du fils */
    
    pidended=wait(&status);
    printf("le fils %d est terminé son status est %d\n",pidended,status);

 /** UNIQUEMENT POUR COMPARER, sinon inutile pour l'exercice en lui même 
  * constater la différence entre execv et execvp
  * execvp comme bash recherche le programme en tenant compte du path
  * execv 
  */
    printf("\n%d mon fils est %d\n", getpid(),pid);
    execv (argv[1], argv+1);
    perror("\n execv du père...");
    
}
