/**
  * Un include est une insertion de code comme un copy/paste
  */
#include <unistd.h>

/** 
 * Standard file descriptors. issue de unistd.h
 *  STDIN_FILENO    0       Standard input. 
 *  STDOUT_FILENO   1       Standard output.  
 *  STDERR_FILENO   2       Standard error output.
 */

/**************/
/* La fonction main point d'entré des programmes en C */
/* main renvoie un code (nous verrons ceci plus tard) */

int main () {
    write(STDOUT_FILENO, "bonjour la classe\n",18);
}

/**
  * pour compiler et générer un executable
  * gcc -o <nomdevotrechoix> <Votre programme.c>
  * dans notre cas
  * gcc -o pgm1 premierP.c
  * si vous omettez -o gcc génère l'executable a.out
  */
