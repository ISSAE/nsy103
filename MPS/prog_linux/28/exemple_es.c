#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main () {
	int fd;
	int v;
	fd=open("toto.txt",O_CREAT|O_RDWR);
        printf("> ");
 	scanf("%d",&v);
	printf("v=%d\n",v);
	dup2(fd,1);
	printf("v=%d\n",v);
	close(fd);
}

