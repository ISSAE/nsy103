#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct {
    long type;
    char texte [256];

} message_t;

int
main(int argc, char * argv []) {
    key_t key;
    message_t message;
    int file;
    long type;

    if (argc != 3) {
        fprintf(stderr, "Syntaxe : %s fichier_clé type \n",
                argv [0]);
        exit(1);
    }
    if ((key = ftok(argv [1], 0)) == -1) {
        perror("ftok");
        exit(1);
    }
    if (sscanf(argv [2], "%ld", & type) != 1) {
        fprintf(stderr, "Type invalide");
        exit(1);
    }
    if ((file = msgget(key, IPC_CREAT | 0600)) == -1) {
        perror("msgget");
        exit(1);
    }
    if (msgrcv(file, (void *) & message, 256, type, 0) >= 0)
        fprintf(stdout, "(%ld) %s \n", message . type, message . texte);
    else
        perror("msgrcv");
    return (0);
}
