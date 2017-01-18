#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

typedef struct {
    long type;
    char texte [256];

} message_t;

typedef _point {
    int x;
    int y;
} point;

int
main(int argc, char * argv []) {
    key_t key;
    message_t message;
    int file;
    point.x=3; point.y=5;
    if (argc != 4) {
        fprintf(stderr, "Syntaxe : %s fichier_clé type message \n",
                argv [0]);
        exit(1);
    }
    if ((key = ftok(argv [1], 0)) == -1) {
        perror("ftok");
        exit(1);
    }
    if ((sscanf(argv [2], "%ld", & (message . type)) != 1)
            || (message . type <= 0)) {
        fprintf(stderr, "Type invalide");
        exit(1);
    }
    strncpy(message . texte, argv [3], 255);
    message . texte [255] = '\0';

    memcpy(message . texte, point, sizeof(struct _point));
    if ((file = msgget(key, IPC_CREAT | 0600)) == -1) {
        perror("msgget");
        exit(1);
    }
    if (msgsnd(file, (void *) & message, 256, 0) < 0) {
        perror("msgsnd");
        exit(1);
    }
    return (0);
}
