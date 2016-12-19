#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main () {
	int fd;
	int v;
	fd=open("toto.txt",O_CREAT|O_RDWR);
        printf("> ");
 	scanf("%d",&v);
	printf("un printf : v=%d\n",v);
        dprintf(fd, "direct : v=%d\n",v);
	dup2(fd,1);
	printf("après dup : v=%d\n",v);
	close(fd);
}

