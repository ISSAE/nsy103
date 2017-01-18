#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

int
main(int argc, char * argv []) {
    key_t key;
   
    int shm;
    char * chaine = NULL;

    if (argc != 2) {
        fprintf(stderr, "Syntaxe : %s fichier_cl� \n", argv [0]);
        exit(1);
    }
    if ((key = ftok(argv [1], 0)) == -1) {
        perror("ftok");
        exit(1);
    }
    if ((shm = shmget(key, 0, 0)) == -1) {
        perror("semget/shmget");
        exit(1);
    }
    if ((chaine = shmat(shm, NULL, SHM_RDONLY)) == NULL) {
        perror("shmat");
        exit(1);
    }
    
    fprintf(stdout, "%p %s\n", chaine, chaine);
    
    return (0);
}

