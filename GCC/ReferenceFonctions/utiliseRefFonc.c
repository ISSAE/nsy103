#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "signatures.h"


int main(int argc, char**argv, char**env){
    int x,y;
    if (argc!=4) {
        printf("Pour utiliser le programme faire :\n ./lance <nomfonction> <param1> <param2>\n");
    }
    //Si on est ici donc argc==4 argv[1] : nom de la fonction argv[2] et argv[3] les paramètres]
    //Récupération d'un  entier depuis une chaine de caractère : solution 1
    x=atoi(argv[2]);
    //Récupération d'un  entier depuis une chaine de caractère : solution 2
    sscanf(argv[3], "%d", &y);
#ifdef DEBUG
    printf("x=%d,y=%d\n",x,y);
#endif
    if (strcmp(argv[1],"add")==0) {
        //On demande add
        printf("%s(%d,%d)=%d\n", argv[1],x,y,applyF(fadd,x,y));
    } else if (strcmp(argv[1],"mult")==0) {
        //on demande mult
        printf("%s(%d,%d)=%d\n", argv[1],x,y,applyF(fmult,x,y));
    } else {
        //Operation inconnue
        printf("%s n'est pas définie ... désolé\n",argv[1]);
    }
}
