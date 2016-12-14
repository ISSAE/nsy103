#include <unistd.h>
#include <stdio.h>

int main() {

    int p;

    printf("Je suis %d mon père est %d\n", getpid(), getppid());

    p = fork();

    //Combien de fois ce prinf sera executé? pourquoi?
    printf("p = %d : Je suis %d mon père est %d\n", p, getpid(), getppid());

    if (p == 0) {
        printf("Je suis le fils : Je suis %d mon père est %d\n", getpid(), getppid());
    } else {
        printf("Je suis le père : Je suis %d mon père est %d mon fils est %d\n", getpid(), getppid(), p);
    }

}
