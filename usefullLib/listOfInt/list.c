#include "list.h"
#include <stdlib.h>
#include <stdio.h>

plist new() {
    return NULL;
}

plist cons(int v, plist reste) {
    //printf("cons %d et ",v); printList(reste);
    plist newl = (plist) malloc(sizeof (list));
    newl->valeur = v;
    newl->suiv = reste;
    return newl;
}

plist reste(plist l) {
    return l->suiv;
}

int tete(plist l) {
    return l->valeur;
}

plist find(int v, plist l) {
    if (l == NULL) return l;
    if (tete(l) == v) return l;
    else return (find(v, reste(l)));
}


plist suprime(int v, plist l) {
    //printf("suprime %d de",v); printList(l);
    plist ret;
    if (l == NULL) ret=NULL;
    else if (tete(l) == v) {
        ret=reste(l);
        free(l);
    } else ret= cons(tete(l), suprime(v,reste(l)));
    //printf("retour de suprime %d est ",v); printList(ret);  
    return ret;
}


void _printList(plist l) {
    if (l != NULL) {
        if (l->suiv != NULL) {
            printf("%d . ", tete(l));
            _printList(reste(l));
        } else {
            printf("%d", tete(l));
        }
    }
}

void printList(plist l) {
    printf("(");
    _printList(l);
    printf(")\n");
}






