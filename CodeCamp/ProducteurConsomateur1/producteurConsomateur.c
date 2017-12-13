#include "BufferCirc.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10

/** Exercice AFAIRE
 * ajouter l'utilisation des semaphore et 2 threads
 * 1 producteur
 * 1 consomateur
 * dans le buffer
 */

struct _buffer_circ *buff;


//---------------------------------------------------------
// test produire

int produire() {
  int res = rand();
  printf("J'ai produit %d\n", res);
  return res;
}
void consomer(int elem) { printf("Je consome %d\n", elem); }

// Les fonction de test
// Le squelette des 2 threads===============================
void *producteur(void *args) {
  int data;
  while (1) {
    data = produire();
    ajouterBC(buff, (void *)(intptr_t)data);
    // ajouter(data);
  }
}

void *consomateur(void *args) {
  int data;
  while (1) {
    // data = prendre();
    data = (int)(intptr_t)retirer(buff);
    consomer(data);
  }
}
//==========================================================
int main() {
  int i;
  // tester le buffer
  buff = newBufferCirc(10);
  pthread_t t1;
  pthread_t t2;
  pthread_create(&t1, 0, producteur, 0);
  pthread_create(&t2, 0, consomateur, 0);

  pthread_join(t1, 0);
  pthread_join(t2, 0);
}
