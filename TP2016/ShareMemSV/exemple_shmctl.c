#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define LG_CHAINE 256

int
main(int argc, char * argv []) {
    key_t key;
    int sem;
    int shm;

    if (argc != 2) {
        fprintf(stderr, "Syntaxe : %s fichier_clé \n", argv [0]);
        exit(1);
    }
    if ((key = ftok(argv [1], 0)) == -1) {
        perror("ftok");
        exit(1);
    }
    if (((sem = semget(key, 1, 0)) == -1)
            || ((shm = shmget(key, LG_CHAINE, 0)) == -1)) {
        perror("semget/shmget");
        exit(1);
    }
    shmctl(shm, IPC_RMID, NULL);
    semctl(sem, IPC_RMID, 0);
    return (0);
}

