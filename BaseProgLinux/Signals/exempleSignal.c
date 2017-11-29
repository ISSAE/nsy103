/**
 * Exemple d'utilisation signal().
 */
 #include <stdio.h>
 #include <unistd.h>
 #include <signal.h>
 #include <string.h>


 /**
  * Le handler associé au signal
  */
static void hand (int sig) {
    printf ("Siganl %d j'ai aucune autre info! et c'est souvent suffisant\n", sig);
}
  
int main (int argc, char *argv[]) {
     
     if (signal(SIGTERM, &hand) < 0) {
         perror ("signal");
         return 1;
     }

     while (1)
         sleep (10);
  
     return 0;
 }