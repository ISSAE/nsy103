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
    char * chaine = NULL;


    if (argc != 2) {
        fprintf(stderr, "Syntaxe : %s fichier_clé \n", argv [0]);
        exit(1);
    }
    if ((key = ftok(argv [1], 0)) == -1) {
        perror("ftok");
        exit(1);
    }
    if ((shm = shmget(key, LG_CHAINE, IPC_CREAT | 0600)) == -1) {
        perror("shmget");
        exit(1);
    }
    if ((chaine = shmat(shm, NULL, 0)) == NULL) {
        perror("shmat");
        exit(1);
    }

    fprintf(stdout, "> ");
    fgets(chaine, LG_CHAINE, stdin);
    printf("%p",chaine);
    return (0);
}

