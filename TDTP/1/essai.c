#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv) {
	int pid;
	pid = fork();
	if (pid == 0) {
		for(;;)
		printf ("je suis le fils\n");
	}
	else {
		for(;;)
		printf("je suis le père\n");
	}
}
