#include <unistd.h>
#include <stdio.h>

main() {

    int res = fork();
    if (res > 0) {
        printf("je suis le père pid= %d, ppid= %d\n", getpid(), getppid());
        res = fork();
        if (res > 0) {
            printf("je suis le père pid= %d, ppid= %d\n", getpid(), getppid());


        } else if (res == 0) {

            printf("je suis le fils pid= %d, ppid= %d\n", getpid(), getppid());

        } else {
            printf("Erreure :(");
        }
    } else if (res == 0) {

        printf("je suis le fils pid= %d, ppid= %d\n", getpid(), getppid());

    } else {
        printf("Erreure :(");
    }
}