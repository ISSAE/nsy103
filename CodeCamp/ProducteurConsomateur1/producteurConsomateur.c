#include "BufferCirc.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10

/** Exercice AFAIRE
 * ajouter l'utilisation des semaphores aux 2 threads
 * 1 producteur
 * 1 consomateur
 * dans le buffer
 * Il y a 2 problèmes a resoudres
 * A: La synchronisation entre producteur et consomateur et la taille du buffer
 * B: La resource critique qui sont les indexs du Buffer (debut,fin et nb)
 */

 // Le buffer un donné globale partagée par tous les threads
struct _buffer_circ *buff;


//---------------------------------------------------------
// test produire et consomer 2 fonctions qui simulent la production de quelques choses
// -------------------------------------------------------
int produire() {
  int res;
  res = rand();
  printf("J'ai produit %d\n", res);
  return res;
}
void consomer(int elem) { printf("Je consome %d\n", elem); }

// Les fonctions (thread) pour simuler les "services" de production et consomation
// Le squelette des 2 threads===============================
/**
 * produire indéfiniment
 * ALGO
 *   produire quelque chose
 *   le déposer dans le buffer
 */
void *producteur(void *args) {
  int data;
  while (1) {
    data = produire();
    ajouterBC(buff, (void *)(intptr_t)data);
    // ajouter(data);
  }
}
/**
 * consomer indéfiniment
 * ALGO
 *   recuperer quleue chose du buffer
 *   puis le consomer (ie le traiter)
 */
void *consomateur(void *args) {
  int data;
  while (1) {
    // data = prendre();
    data = (int)(intptr_t)retirer(buff);
    consomer(data);
  }
}
//
// La question! comment savoir que tous les messages produits seront consomés correctement???
//==========================================================

/**
 * main : initialisation et lancement des 2 Threads
 */
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
