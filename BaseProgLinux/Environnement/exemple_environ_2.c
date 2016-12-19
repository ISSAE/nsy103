
#include <stdio.h>

//L'environnement est aussi passé en argunme du main
//Par le SE
int main(int argc, char * argv [], char * envp []) {
    int i = 0;

    for (i = 0; envp [i] != NULL; i++)
        fprintf(stdout, "%d : %s\n", i, envp [i]);

    return (0);
}
