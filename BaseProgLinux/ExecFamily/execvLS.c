#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (void) {
	//system ("ls -l");
        execlp ("./listeArgs", "listeA", "abc", "123", "-l",NULL);
        printf("---------------\n");
	return (0);
}
