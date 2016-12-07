#include <stdio.h>

//Variable globale de l'environnement
//Tableaux de string
//une string est tableau de char
extern char ** environ;

int main(void) {
    int i = 0;

    for (i = 0; environ [i] != NULL; i++)
        fprintf(stdout, "%d : %s\n", i, environ [i]);

    return (0);
}
