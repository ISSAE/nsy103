#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

/**
 * Ce programme, à première vue « innocent », pourrait causer un interblocage. 
 * Imaginons le scénario suivant. 
 * Le fils est suspendu juste après le kill() et le noyau donne la main au père, 
 * qui est en pause(). 
 * Le père se réveille, affiche le nombre suivant, 
 * émet le signal et s'endormit à nouveau. 
 * Le noyau délivre le signal au fils et il reprend son exécution par le handler(), 
 * suivi par une pause() qui ne finit jamais. On peut bricoler le remède suivant.
 */

void handler(int sig) {
}

int main(void) {
    pid_t pid;
    int i;

    if (signal(SIGUSR1, handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { /* fils */
        pid = getppid();
        for (i = 1; i <= 100; i += 2) {
            printf("%d\n", i);
            kill(pid, SIGUSR1);
            pause();
        }
    } else { /* père */
        for (i = 2; i <= 100; i += 2) {
            pause();
            printf("%d\n", i);
            kill(pid, SIGUSR1);
        }
    }

    return 0;
}
