#include "f.h"
#include<stdio.h>

/**
  * sudo apt install manpages-fr manpages-fr-extra manpages manpages-posix manpages-fr-dev manpages-posix-dev manpages-dev
  * pour installer les pages de manuel man
  */

int main () {

  /* faire 
   * man 3 printf
   * pour savoir comment fonctionne printf
   */

   /* ici f est une fonction que nous allons definir dans un autre fichier */
   /* remarque ici NB n'est pas une variable mais une macro */
   printf("f(%d)=%d\n",NB,f(10));
}


