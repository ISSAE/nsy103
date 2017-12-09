[Index Home](/) |
----

# Les Sémaphores
## Description

La plus importante contribution au problème de la synchronisation entre processus fut l'introduction par _**Dijkstra**_, en _**1965**_, du concept des Sémaphores.

Conceptuellement, un sémaphore joue le rôle d'un _**distributeur de tickets**_, qui, initialement dispose d'un certain nombre de tickets, éventuellement nul.

Un processus utilisateur du sémaphore _**demande un ticket**_ en _**invoquant**_ une opération particulière appelée _**P**_ : _**si**_ au moins _**un ticket est disponible**_, le processus appelant _**le prend et poursuit**_ son exécution ; _**dans le cas contraire**_, le demandeur est enregistré dans une file d'attente et _**est bloqué**_ dans l'attente de l'obtention d'un ticket. Autrement dit, _**l'opération P**_ n'est exécutable par le processus appelant _**que s'il existe un ticket libre**_, elle _**peut se retrouver bloquante**_ dans le cas contraire.

Grâce à une _**opération inverse**_, appelée _**V**_, un processus _**dépose son ticket**_ dans le distributeur. _**Si**_ des _**processus**_ sont _**en attente**_ dans la file du sémaphore, _**le premier**_ d'entre eux _**est débloqué**_ et obtient son ticket.

Plus précisément, un sémaphore est une _**variable entière <u>non négative</u>**_ à laquelle, sauf pour l'initialisation, on accède _**seulement à travers deux opérations**_ standards atomiques (non interruptibles) : _**P et V**_.

*   _**P**_, de l'hollandais proberen (tester), aussi appelé parfois wait, consiste à _**décroître la valeur du sémaphore**_ d'une unité _**à condition**_ que le résultat ne devienne <u>_**pas négatif**_</u>. En effet, _**dans le cas**_ ou un processus effectue P et que la _**valeur**_ du sémaphore est _**de zéro**_, alors ce dernier _**se retrouve gelé**_ jusqu'à ce que cette valeur redevienne supérieur strictement à zéro et qu'il puisse alors la décrémenter.

*   _**V**_, pour  Verhogen  (incrémenter), aussi appelé parfois signal, consiste simplement à _**accroître la valeur du sémaphore**_ d'une unité.

Ce mécanisme _**permet**_ donc de _**limiter l'exécution d'une portion de code** _(et donc l'accès à une ressource quelconque), encadrée par des appels respectifs à P et à V, _**à un nombre fixé**_ de processus. Nous allons voir par la suite, que cela permet de réaliser l'exclusion mutuelle nécessaire à la prévention des conflits d'accès aux données non partageables.


## Les sémaphores sous Linux

Il existe deux ensembles de primitives pour réaliser des sémaphores sous Linux:
1. Les sémaphores de la norme System V, plutôt adapté a la synchronisation inter-processus (décrit dans cette page). 
2. Les [sémaphore de la norme POSIX](/BaseProgLinux/Threads/SemaphoreTh.md) plutôt adapté au concurrence inter-thread

### présentation sémaphores System V

La gestion des sémaphores sous Unix, est prise en compte par des _**primitives systèmes**_ (system calls) étant donné leur principe de fonctionnement très bas niveau et la nécessité d'avoir les opérations P et V qui ne soient pas interruptibles. Les sémaphores sont donc gérés par le noyau, ils appartiennent à la classe des objets IPC.

La technique IPC Unix système V, propose un ensemble de mécanismes purement mémoires, qui permettent dans des limites de droits, à n'importe quels couples de processus _**d'échanger des informations et/ou de se synchroniser**_. Les objets IPC sont composés en :

*   des _**files de messages**_, aussi appelées queues de messages ("messages", abrégé msg), Les processus ont le loisir de créer une file d'attente, de la supprimer, d'y ajouter ou d'en retirer un message. Ces files gérées directement dans l'espace noyau recevront des messages de différents types et tailles.

*   des _**mémoires partagées**_ ("shared memory", abrégé shm), Les mémoires partagées sont des segments de mémoire qui peuvent, comme leur nom l'indique être partagé par plusieurs processus, avec les problèmes d'exclusion mutuelle que peut impliquer.

*   et des _**sémaphores**_ ("semaphore", abrégé sem), Sémaphores que l'on ne présente plus...

Le point commun des objets IPC, et qui nous intéresse plus particulièrement en ce qui concerne les sémaphores, est qu'ils forment des _**ressources maintenues par le noyau**_ dans son espace personnel ; ils sont donc _**indépendants d'un processus particulier**_. Chaque processus ne fait que requérir auprès du noyau l'obtention et l'utilisation de ceux-ci.

A cette double fin (centralisation et partage), Unix maintient pour tout type d'objet IPC, une table personnelle identifiant chacune des instances crées. Ceci explique pourquoi, les files de messages, les mémoires partagées et les sémaphores sont _**tous identifiés sous la forme d'un entier**_ (type **_int_**) souvent appelé xxxid (ou xxx est soit msg pour les files, shm pour les mémoires ou sem pour les sémaphores) ou encore clé.

L'IPC sémaphore d'Unix possède deux généralisations qui en enrichissent encore l'utilisation.

*   _**Incrémentation**_ et _**décrémentation**_ d'un sémaphore _**par un entier quelconque**_ pas seulement 1.
*   _**Possibilité**_ _**d'agir**_ sur _**plusieurs sémaphores**_ de manière atomique (non-interruptible), _**un IPC de type sémaphore**_ gèrant par conséquence <u>_**non pas un seul**_</u> sémaphore, mais _**un tableau de sémaphore**_, chacun étant identifié par son rang dans le tableau (0 pour le premier).

#### création ou acquisition

Pour créer, ou acquérir un sémaphore, on dispose de la primitive suivante :

```C 
int semget(key_t cle, int nsems, int semflag);
```

Cette fonction _**crée le sémaphore**_ si celui-ci n'existe pas, _**ou renvoie un identificateur**_ sur ce dernier _**s'il a déjà été créé**_ par un autre processus.

Les paramètres :

*   cle, constante symbolique pour identifier le sémaphore à sa création
*   nsems, est le nombre de sémaphore(s) souhaité(s) dans le tableau
*   semflag, représente les droits souhaités, généralement : IPC_CREAT | 0700

En retour, la fonction renvoie soit -1 si une erreur c'est produite, ou alors l'identificateur (semid) du sémaphore.

Ex. pour créer un sémaphore simple :

```C
semid = semget(cle, 1, IPC_CREAT | 0700);
```

#### initialisation

Pour affecter une valeur initiale (le nombre de jetons) à un sémaphore, on utilise la primitive semctl(), qui permet aussi entre autre, comme nous le verrons plus tard, de libérer un sémaphore.

```C
int semctl(int semid, int semnum, SETVAL, int valeur);
```

Les paramètres :

*   semid, identificateur du sémaphore au niveau du système (voir précédemment)
*   semnum, indice du sémaphore dans le sous-ensemble
*   SETVAL, pour indiquer au noyau que l'on désire affecter une valeur au sémaphore
*   valeur, valeur initiale

En retour, la fonction renvoie soit -1 si une erreur s'est produite.

Ex. pour initialiser un sémaphore simple à 1 (identifié par semid) :
```C
valRet = semctl(semid, 0, SETVAL, 1);
```

#### utilisation (Écriture de P et V)

En ce qui concerne les opérations P et V, elles peuvent être réalisées par des appels directs à la primitive système semop(), de la manière suivante :

```C
void p(int semid) {
    int rep;
    struct sembuf pd={0,-1,0};
    rep=semop(semid, &pd, 1);
    return(rep);
}

void v(int semid) {
    int rep;
    struct sembuf pd={0,1,0};
    rep=semop(semid, &pd, 1);
    return(rep);
}
```

**NB :** il est _**très important**_ pour le bon fonctionnement de ces deux opérations, que _**leur code ne comportent uniquement que des appels à**_ _**semop()**_ et rien de plus, car seul le déroulement de cette primitive est garanti comme n'étant pas interruptible par le noyau ! Cette précaution est nécessaire pour préserver le caractère atomique de ces deux opérations.

#### Opération sur sémaphore System V

La primitive semop() permet d'augmenter ou de diminuer la valeur d'un sémaphore, et comme nous l'avons vu précédemment, elle peut le faire avec un nombre d'une valeur quelconque et sur un sémaphore qui peut éventuellement être décomposé en un sous-ensemble de sémaphore.

```C
int semop(int semid, struct sembuf *sops, size_t nsops);
```
Les paramètres :

*   semid, identificateur du sémaphore au niveau du système
* sops, est une structure composée de 3 nombres :
  *   sem_num, l'indice de départ du (ou des) sémaphore(s) à traiter,
  *   sem_op, la valeur à appliquer au sémaphore,
  *   et sem_flg, un drapeau (flag) qui sera renseigné par le système.
*   nsops, nombre de sémaphore(s) a traiter (à partir de l'indice de départ de sops)

Dans le cas précédent, un seul sémaphore (non décomposable) nous suffit, donc la plupart de ces paramètres sont à zéro.

_**L'action**_ réelle de semop()_**dépend de la valeur du paramètre** __**sem_op**_ :

*   si celle-ci est _**strictement supérieur à 0**_, alors elle est _**ajoutée à celle du sémaphore**_. Les processus en attente de l'augmentation du sémaphore sont réveillées par Unix.
*   si par contre elle est _**strictement inférieur à 0**_, alors la _**valeur**_ absolue de sem_op est _**retirée du sémaphore**_. Dans le cas ou cette valeur absolue est plus grande que celle du sémaphore (le nombre de jeton), alors le processus s'endort.
*   enfin, dans le cas ou la valeur transmise est _**égal à 0**_, cela permet de _**tester si le sémaphore est à 0**_ et donc de déterminer éventuellement _**si l'opération P**_ sera _**bloquante**_.

Ainsi, dans les définitions précédentes de P et de V, on peut remarquer que le paramètre sem_op prend respectivement la valeur -1 (pour décrémenter le sémaphore) et la valeur 1 (pour l'incrémenter).

_Remarque:_

*   au niveau du noyau, les _**processus endormis**_ sous placé dans une file d'attente similaire à celle qui regroupe les processus en attente d'une entrée/sortie, ils _**ne consomment**_ donc _**plus de temps CPU**_.
*   les processus _**sommeillent**_ dans un _**mode <interruptible<**_, ils sont donc _**sensible aux signaux**_ !

#### libération

La libération d'un sémaphore est faite par un appel à semctl(), a qui l'on transmet l'identificateur du sémaphore, ainsi que la commande IPC_RMID.

`int semctl(int semid, IPC_RMID, NULL);`

Les paramètres :

*   semid, identificateur du sémaphore au niveau du système
*   IPC_RMID, pour indiquer au noyau que l'on souhaite supprimer le sémaphore

En retour, la fonction renvoie soit -1 si une erreur s'est produite.

Ex. pour libérer un sémaphore (identifié par semid) :

`valRet = semctl(semid, IPC_RMID, NULL);`

