/* 
 * File:   main.c
 * Author: pascalfares
 *
 * Created on 26 octobre 2015, 09:16
 */

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
    /* declaration d'un tableaux (statique) */
    int T[10]; /* tableaux de 10 entiers de T[0] à T[9] */
    int i;
    /* remplir le tableaux */
    for (i=0; i< 10; i++) {
           T[i]=i;
    }

    /* Afficher les éléments du tableaux notation t[] */
    for (i=0; i< 10; i++) {
           printf("T[%d]=%d\n",i,T[i]);
    }

    /* En fait T est une référence vers une adresse mémoire (le début du tabeaux) */
    /* *T represente la valeur di premier élément du tableau *(T+1) le deixième et *(T+i) le ième... */
    /* en fait T[i] est éauivalent à *(T+i) */
    
    for (i=0; i< 10; i++) {
           printf("*(T+%d)=%d\n",i,*(T+i));
    }

    /* Que se passe t'il si on va plus loin que 10? */
    while (1) {
          /* UNe boucle infinie */
          printf("T[%d]=%d\n",i,T[i]);
          i++;
   }
    return (EXIT_SUCCESS);
}

