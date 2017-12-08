/**
 * Exemple d'utilisation sigaction() avec un handler de signal à 3 arguments
 * incluant [siginfo_t](Exemples.md/#siginfo).
 */
 #include <stdio.h>
 #include <unistd.h>
 #include <signal.h>
 #include <string.h>
  
 /**
  * Le handler associé au signal (utilisation du champ sa_sigaction)
  */
static void hdl (int sig, siginfo_t *siginfo, void *context) {
     printf ("Siganl %d issue de  PID: %ld, UID: %ld\n", sig,
             (long)siginfo->si_pid, (long)siginfo->si_uid);
 }

 /**
  * Le handler associé au signal (utilisation du champ sa_handler)
  */
static void hand (int sig) {
    printf ("Siganl %d j'ai aucune autre info! et c'est souvent suffisant\n", sig);
}

static void ctrC (int sig) {
   printf ("Je ne veux pas m'arreter\n");
}
  
 int main (int argc, char *argv[]) {
     struct sigaction act;
     struct sigaction acth;
  
     /* initialisation (pour être sure!) */
     memset (&act, '\0', sizeof(act));
     memset (&acth, '\0', sizeof(acth));
  
     /* Use the sa_sigaction field because the handles has two additional parameters */
     act.sa_sigaction = &hdl;
     /* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */
     act.sa_flags = SA_SIGINFO; 
     if (sigaction(SIGTERM, &act, NULL) < 0) {
         perror ("sigaction");
         return 1;
     }
  
    acth.sa_handler = &hand;
     

    printf ("SIGUSR1 = %d\n",SIGUSR1);
    if (sigaction(SIGUSR1, &acth, NULL) < 0) {
        perror ("sigaction");
        return 1;
    }

    signal(SIGINT,ctrC);

    while (1)
         sleep (10);
  
     return 0;
 }