#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s commande [arg] [arg] ...\n", argv[0]);
        exit(1);
    }
    if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
        perror("signal");
        exit(1);
    }
    execvp(argv[1], argv + 1);
    perror("execvp");
    exit(1);
}

