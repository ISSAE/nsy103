#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    printf("PID %d : Je suis un programme qui imprime c'est tout\n", getpid());
}
