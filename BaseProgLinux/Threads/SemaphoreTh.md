[Index Home](/) | [Threads](.) | [<- Base Programmation Linux](..) 
-----------------|-------------| ------------------

Voir aussi <a class="buttons github" href="https://github.com/ISSAE/nsy103/tree/master/BaseProgLinux/Threads">Les exemples: présents dans GitHub</a>

---

Le problème de la coordination entre threads est un problème majeur (vois exemple d'un progromme ne fonctionnant pas correctement [concurence.faux.c](https://github.com/ISSAE/nsy103/blob/master/BaseProgLinux/Threads/concurence.fux.c) et sa version correcte [concurence.c](https://github.com/ISSAE/nsy103/blob/master/BaseProgLinux/Threads/concurence.c). Outre les [mutex](MutexTh) adapté aux exclusion mutuelles, d’autres solutions à ce problème ont été développées. Historiquement, une des premières propositions de coordination sont les sémaphores [Dijkstra]. Un sémaphore est une structure de données qui est maintenue par le système d’exploitation et contient :

un entier qui stocke la valeur, positive ou nulle, du sémaphore.
une queue qui contient les pointeurs vers les threads qui sont bloqués en attente sur ce sémaphore.
Tout comme pour les mutex, la queue associée à un sémaphore permet de bloquer les threads qui sont en attente d’une modification de la valeur du sémaphore.

Une implémentation des sémaphores se compose en général de quatre fonctions :

1. une fonction d’initialisation qui permet de créer le sémaphore et de lui attribuer une valeur initiale nulle ou positive.
2. une fonction permettant de détruire un sémaphore et de libérer les ressources qui lui sont associées.
3. une fonction post (V) qui est utilisée par les threads pour modifier la valeur du sémaphore. S’il n’y a pas de thread en attente dans la queue associée au sémaphore, sa valeur est incrémentée d’une unité. Sinon, un des threads en attente est libéré et passe à l’état Ready.
4. une fonction wait (P) qui est utilisée par les threads pour tester la valeur d’un sémaphore. Si la valeur du sémaphore est positive, elle est décrémentée d’une unité et la fonction réussit. Si le sémaphore a une valeur nulle, le thread est bloqué jusqu’à ce qu’un autre thread le débloque en appelant la fonction post.
Les sémaphores sont utilisés pour résoudre de nombreux problèmes de coordination. Comme ils permettent de stocker une valeur entière, ils sont plus flexibles que les _mutex_ qui sont utiles surtout pour les problèmes d’exclusion mutuelle.


# Description des sémaphores POSIX (librairie pthread)

La librairie de gestion des threads offre les fonctions ci-dessous pour créer et utiliser des sémaphores. Attention : ces sémaphores sont propres à un processus. Ils permettent de synchroniser plusieurs threads entre eux, mais ils ne peuvent synchroniser plusieurs processus. Pour réaliser cette synchronisation il faut se tourner vers les [sémaphores système V](/ProgAvancee/SemaphorePourProc/semaphor) basés sur les IPC (Inter Processus Communication) .

* `int [sem_init](#sem_init) (sem_t *semaphore, int pshared, unsigned int valeur)`
> Création d'un sémaphore et préparation d'une valeur initiale.
* `int sem_wait(sem_t * semaphore);`
  > Opération P sur un sémaphore.
* `int sem_trywait(sem_t * semaphore);`
  > Version non bloquante de l'opération P sur un sémaphore.
* `int sem_post(sem_t * semaphore);`
  > Opération V sur un sémaphore.
* `int sem_getvalue(sem_t * semaphore, int * sval);`
  > Récupérer le compteur d'un sémaphore.
* `int sem_destroy(sem_t * semaphore);`
  > Destruction d'un sémaphore.

Bien entendu, une aide plus complète peut être obtenue sur chaque fonction en utilisant le manuel UNIX :

man nom_de_la_fonction

# sem_init 
- Initialiser un sémaphore non nommé

```C
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);

Effectuez l'édition des liens avec l'option -pthread.
```
# DESCRIPTION
sem_init()  initialise le sémaphore non nommé situé à l'adresse pointée par sem. L'argument value spécifie la valeur initiale du sémaphore.

L'argument pshared indique si  ce  sémaphore  sera  partagé  entre  les threads d'un processus ou entre processus.

Si pshared vaut 0, le sémaphore est partagé entre les threads d'un même processus et devrait être situé à une adresse visible par tous les threads par  exemple,  une variable globale ou une variable allouée dynamiquement dans le tas).

Si pshared n'est pas nul, le sémaphore est partagé entre  processus  et devrait  être  situé  dans  une  région  de mémoire partagée (consultez shm_open, mmap et shmget) (puisqu'un fils  créé  avec  fork hérite de la projection mémoire du père, il peut accéder au sémaphore). Tout processus qui peut accéder à la région de  mémoire  partagée  peut opérer sur le sémaphore avec sem_post, sem_wait, etc. **Préférer Les _[sémaphores système V](/ProgAvancee/SemaphorePourProc/semaphor)_ dans le cas de sémaphore inter-processus**

L'initialisation d'un sémaphore qui a déjà été initialisé résulte en un comportement indéfini.

