#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

#define LG_CHAINE 256

int
main(int argc, char * argv []) {
    key_t key;
    int shm;

    if (argc != 2) {
        fprintf(stderr, "Syntaxe : %s fichier_cl� \n", argv [0]);
        exit(1);
    }
    if ((key = ftok(argv [1], 0)) == -1) {
        perror("ftok");
        exit(1);
    }
    if ((shm = shmget(key, LG_CHAINE, 0)) == -1) {
        perror("semget/shmget");
        exit(1);
    }
    shmctl(shm, IPC_RMID, NULL);

    exit(0);
}

