#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>



int main(int argc, char **argv, char **envp) {
    int i;
    printf("mon id =%u mon pere id est %u\n", getpid(), getppid());
    while(1) {
         printf("<%u>", getppid());
    }
}
