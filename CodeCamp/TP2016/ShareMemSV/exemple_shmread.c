#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

int
main(int argc, char * argv []) {
    key_t key;
    int sem;
    int shm;
    struct sembuf sembuf;
    char * chaine = NULL;

    if (argc != 2) {
        fprintf(stderr, "Syntaxe : %s fichier_clé \n", argv [0]);
        exit(1);
    }
    if ((key = ftok(argv [1], 0)) == -1) {
        perror("ftok");
        exit(1);
    }
    if (((sem = semget(key, 1, 0)) == -1)
            || ((shm = shmget(key, 0, 0)) == -1)) {
        perror("semget/shmget");
        exit(1);
    }
    if ((chaine = shmat(shm, NULL, SHM_RDONLY)) == NULL) {
        perror("shmat");
        exit(1);
    }
    sembuf . sem_num = 0;
    sembuf . sem_op = -1;
    sembuf . sem_flg = 0;
    if (semop(sem, & sembuf, 1) < 0) {
        perror("semop");
        exit(1);
    }
    fprintf(stdout, "%s\n", chaine);
    sembuf . sem_op = 1;
    if (semop(sem, & sembuf, 1) < 0) {
        perror("semop");
        exit(1);
    }
    return (0);
}

