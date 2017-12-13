# Posix message queues

Dans l’API standard Unix, il existe deux implémentations pour les files de message : les message queue Système V et les message queues Posix. Les premières sont apparues dans les systèmes Unix des années 80. Elles étaient efficaces mais disposaient d’une interface de programmation un peu bancale : il fallait réserver dans le bloc de données à envoyer quatre octets pour stocker la priorité du message. Ceci n’est pas très dérangeant, mais pouvait nécessiter quand même une recopie systématique du message s’il était produit par une bibliothèque indépendante par exemple. En outre, comme l’ensemble des IPC Système V, ces message queues ne s’intégraient pas dans le concept général des descripteurs de fichiers Unix.

Dans les années 90, avec la volonté d’uniformiser les interfaces de programmation des systèmes Unix par l’intermédiaire de la norme Posix, sont apparues de nouvelles files de message, dont l’interface est plus simple, et dont les descripteurs sont plus proches de ceux des fichiers. Les message queues Posix n’ont été intégrées qu’assez tardivement dans Linux (dans la version 2.6.10 si ma mémoire est bonne).

Les appels-système qui nous concernent sont :

```C
#include <mqueue.h>

mqd_t   mq_open    (const char * nom, int flags, mode_t mode, struct mq_attr * attr);
int     mq_send    (mqd_t mq, const char * msg, size_t lg, unsigned int prio);
ssize_t mq_receive (mqd_t mq, char * msg, size_t lg, unsigned int * prio);
int     mq_close   (mqd_t mq);
int     mq_unlink  (const char * nom);
```

et voici un petit exemple

## Le producteur de message
```C
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc,char * argv[])
{
    mqd_t mq;
    struct timeval heure;

    if (argc != 2) {
        fprintf(stderr, "usage: %s nom_file_messagen", argv[0]);
        exit(EXIT_FAILURE);
    }

    mq = mq_open(argv[1], O_WRONLY | O_CREAT, 0600, NULL);
    if (mq == (mqd_t) -1) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    while (1) {
        gettimeofday(& heure, NULL);
        mq_send(mq, (char *) & heure, sizeof(heure), 1);
        sleep(1);
    }
    return EXIT_SUCCESS;
}
```
faire ensuite `gcc -o prod producteur.c -lrt`

## Le consomateur de message

```C
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc,char * argv[])
{
    mqd_t mq;
    int taille;
    char * buffer;
    long int duree;
    struct mq_attr attr;
    struct timeval heure;
    struct timeval * recue;

    if (argc != 2) {
        fprintf(stderr, "usage: %s nom_file_messagen", argv[0]);
        exit(EXIT_FAILURE);
    }

    mq = mq_open(argv[1], O_RDONLY | O_CREAT, 0600, NULL);
    if (mq == (mqd_t) -1) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    if (mq_getattr(mq, & attr) != 0) {
        perror("mq_getattr");
        exit(EXIT_FAILURE);
    }
    taille = attr.mq_msgsize;
    buffer = malloc(taille);

    if (buffer == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    recue = (struct timeval *) buffer;
    while (1) {
        mq_receive(mq, buffer, taille, NULL);
        gettimeofday(& heure, NULL);
        duree  = heure.tv_sec - recue->tv_sec;
        duree *= 1000000;
        duree += heure.tv_usec - recue->tv_usec;
        fprintf(stdout, "%ld usecn", duree);
    }
    return EXIT_SUCCESS;
}
```

Faire ensuite `gcc -o prod producteur.c`
