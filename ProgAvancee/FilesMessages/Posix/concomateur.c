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
        fprintf(stdout, "%ld usecn\n", duree);
    }
    return EXIT_SUCCESS;
}