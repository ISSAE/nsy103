#include <stdio.h>
#define N 10

/** Exercice AFAIRE
 * ajouter l'utilisation des semaphore et 2 threads
 * 1 producteur
 * 1 consomateur
 * dans le buffer
 */

// Definition d'un buffer circulaire -----------------
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
//---------------------------------------------------------
// test produire

int produire() {
    int res = rand();
    printf("J'ai produit %d",res);
    return res;
}
void consomer(int elem) {
    printf("Je consome %d", elem);
}

//Les fonction de test 
//Le squelette des 2 threads===============================
void *producteur(void *args) {
    int data;
    while (1) {
        data = produire();
        ajouter(data);
    }
}

void * consomateur(void *args) {
    int data;
    while (1) {
        data = prendre();
        consomer (data);
    }
}
//==========================================================
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
