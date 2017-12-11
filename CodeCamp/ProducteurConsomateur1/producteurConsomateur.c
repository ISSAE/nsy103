#include <stdio.h>
#define N 10

// Definition d'un buffer circulaire
int buffer[N];
int debut=0;
int fin=0;


void ajouter(int elem) {
    buffer[fin] = elem;
    fin = (fin+1) % N;
}

int prendre() {
    int res = buffer[debut];
    debut = (debut+1)%N;
    return res;
}

int main() {
    int i;
    //tester le buffer

    //ajouter
    for (i=0; i<10; i++) {
        ajouter(i);
        printf("ajouter %d au buffer %d %d \n", i, debut, fin);      
    }
    for (i=0; i< 10; i++){
       printf("prendre suivant du buffer resultat =%d %d, %d\n",
       prendre(), debut,fin);      
    }
   
}
