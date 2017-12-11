[Index Home](/) | [<- Base Programmation Linux](..) 
-----------------|-------------------------------
Voir aussi <a class="buttons github" href="https://github.com/ISSAE/nsy103/tree/master/BaseProgLinux/Threads">Les exemples: présents dans GitHub</a>

# Les primitive pour thread
Un thread ou fil (d'exécution) ou tâche (terme et définition normalisés par ISO/CEI 2382-7:2000 ; autres appellations connues : processus léger, fil d'instruction, processus allégé, exétron, voire unité d'exécution1 ou unité de traitement) est similaire à un processus car tous deux représentent l'exécution d'un ensemble d'instructions du langage machine d'un processeur. Du point de vue de l'utilisateur, ces exécutions semblent se dérouler en parallèle. Toutefois, là où chaque processus possède sa propre mémoire virtuelle, les threads d'un même processus se partagent sa mémoire virtuelle. Par contre, tous les threads possèdent leur propre pile d’appel.

## les primitives

* [Création de thread pthread_create](#pthread_create)
* [Sychronisation entre thread](#pthread_join)
* [Termonasion de thread](#pthread_exit)
* [Semaphore pour threads](SemaphoreTh.md)


# pthread_create
pthread_create - Créer un nouveau thread

```C
#include <pthread.h>
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

Compilez et effectuez l'édition des liens avec l'option __-pthread__.
```

Compilez et effectuez l'édition des liens avec l'option __-pthread__.

## DESCRIPTION
La  fonction  pthread_create()   démarre  un  nouveau  thread  dans le processus appelant.  Le nouveau thread commence par appeler  start_routine() voir [Référence de fonctions](/GCC/ReferenceFonctions);
       arg est passé comme unique argument de start_routine().

Le nouveau thread se termine d'une des manières suivantes :

* Il appelle [pthread_exit](#pthread_exit), en indiquant une valeur de sortie qui sera disponible pour pour un autre thread du même processus qui appelle pthread_join(3).

* Il sort de la routine. C'est équivalent à appeler [pthread_exit](#pthread_exit)  avec la valeur fournie à l'instruction return.

* Il est annulé (voir  pthread_cancel(3)).

* Un des threads du processus appelle exit(3), ou le thread principal sort de la routine main(). Cela entraine l'arrêt de tous les threads du processus.

L'argument attr pointe sur une structure pthread_attr_t dont le contenu est utilisé pendant la création des threads pour déterminer les attributs du nouveau thread. Cette  structure  est initialisée avec pthread_attr_init(3) et les fonctions similaires. Si attr est NULL, alors le thread est créé avec les attributs par défaut.

# pthread_join
NOM
       pthread_join - Joindre un thread terminé

```C
#include <pthread.h>

int pthread_join(pthread_t thread, void **retval);
Compilez et effectuez l'édition des liens avec l'option -pthread.
```
       

## DESCRIPTION
La fonction pthread_join()  attend que le thread spécifié par thread se termine. Si ce thread s'est déjà terminé, pthread_join() revient tout de suite. Le thread spécifié par thread doit être joignable.

Si retval n'est pas NULL, pthread_join() copie la valeur de sortie du thread cible (c'est-à-dire la valeur que le thread cible a fournie à [pthread_exit](#pthread_exit)  dans l'emplacement pointé par *retval. Si le thread cible est annulé, PTHREAD_CANCELED est placé dans *retval.

Si  plusieurs  threads  essaient  simultanément  de  joindre  le  même thread, le résultat est indéfini. Si le thread appelant pthread_join()  est annulé, le thread cible reste joignable (c'est-à-dire qu'il ne sera pas détaché).

# pthread_exit
pthread_exit - Terminer le thread appelant

```C
#include <pthread.h>

void pthread_exit(void *retval);

Compilez et effectuez l'édition des liens avec l'option -pthread.
```
       

## DESCRIPTION
La fonction pthread_exit() termine le thread appelant et renvoie une valeur à travers retval qui, si le thread est joignable, est rendue disponible à un autre thread dans le même processus s'il appelle [pthread_join](#pthread_join).
[Linux programmation système (Index)](http://lps.cofares.net/)

# pthread_self 
Obtenir l'identifiant du thread appelant

```C
#include <pthread.h>

       pthread_t pthread_self(void);

       Compilez et effectuez l'édition des liens avec l'option -pthread.
```

## DESCRIPTION
La  fonction  pthread_self()  renvoie l'identifiant du thread appelant. C'est la même valeur qui est  renvoyée  dans  *thread  dans  l'appel  à [pthread_create](#pthread_create)  qui a créé ce thread.
