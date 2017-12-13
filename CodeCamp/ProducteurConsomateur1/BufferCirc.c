#include <stdio.h>
#include <stdlib.h>
#include "BufferCirc.h"

struct _buffer_circ *newBufferCirc(int taille) {
    struct _buffer_circ *bc;
    bc = (struct _buffer_circ *)malloc(taille*sizeof(struct _buffer_circ));
    bc->taille=taille;
    bc->nb=bc->debut=bc->fin=0; //taille ==fin => buffer vide
    bc->tab=malloc(taille*sizeof(void *)); //tabelau de référence quelconque
    return bc;
}

int ajouterBC(struct _buffer_circ *bc, void *elem) {
     if (bc->nb==bc->taille) {
         //buffer et pein!
         return -1; //un code erreure indiquant buffer plein 
     } else {
         bc->tab[bc->fin]=elem;
         //printf("0. depot de %p dans %p %d\n",elem, bc->tab[bc->fin],bc->fin);
         bc->fin = (bc->fin+1) % (bc->taille);
         bc->nb++;
         //printf("1. après dans %p %d\n",bc->tab[bc->fin],bc->fin);
     }
}
void *retirer(struct _buffer_circ *bc) {
    if (bc->nb==0) {
        //bufferVide!
        return NULL;
    } else {
        void *ret=bc->tab[bc->debut];
        bc->debut = (bc->debut+1) % (bc->taille);
        bc->nb--;
        return ret;
    }
}

void trace(struct _buffer_circ *bc) {
    int i;
    int c;
    printf("nb=%d,\tdebut=%d,\tfin=%d \t:",bc->nb,bc->debut,bc->fin);
    //for(i=bc->debut;i<bc->fin;i++) printf("%p ",bc->tab[i]);
    for (c=0; c<bc->nb; c++) {
        i=(bc->debut + c) % (bc->taille);
        printf("%p ",bc->tab[i]);
    }
    printf(":\n");
}