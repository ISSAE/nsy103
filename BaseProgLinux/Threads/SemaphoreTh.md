[Index Home](/) | [Threads](.) | [<- Base Programmation Linux](..) 
-----------------|-------------| ------------------

## Description des sémaphores POSIX (librairie pthread)

La librairie de gestion des threads offre les fonctions ci-dessous pour créer et utiliser des sémaphores. Attention : ces sémaphores sont propres à un processus. Ils permettent de synchroniser plusieurs threads entre eux, mais ils ne peuvent synchroniser plusieurs processus. Pour réaliser cette synchronisation il faut se tourner vers les [sémaphores système V](/ProgAvancee/SemaphorePourProc/semaphor.md) basés sur les IPC (Inter Processus Communication) .

* int [sem_init](#sem_init) (sem_t *semaphore, int pshared, unsigned int valeur)
> Création d'un sémaphore et préparation d'une valeur initiale.
* int sem_wait(sem_t * semaphore);
> Opération P sur un sémaphore.
* int sem_trywait(sem_t * semaphore);
> Version non bloquante de l'opération P sur un sémaphore.
* int sem_post(sem_t * semaphore);
> Opération V sur un sémaphore.
* int sem_getvalue(sem_t * semaphore, int * sval);
> Récupérer le compteur d'un sémaphore.
* int sem_destroy(sem_t * semaphore);
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

Si pshared n'est pas nul, le sémaphore est partagé entre  processus  et devrait  être  situé  dans  une  région  de mémoire partagée (consultez shm_open, mmap et shmget) (puisqu'un fils  créé  avec  fork hérite de la projection mémoire du père, il peut accéder au sémaphore). Tout processus qui peut accéder à la région de  mémoire  partagée  peut opérer sur le sémaphore avec sem_post, sem_wait, etc. **Préférer Les _[sémaphores système V](/ProgAvancee/SemaphorePourProc/semaphor.md)_ dans le cas de sémaphore inter-processus**

L'initialisation d'un sémaphore qui a déjà été initialisé résulte en un comportement indéfini.
