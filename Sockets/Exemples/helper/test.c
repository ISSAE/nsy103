#include "helperSO.h"

int main(int argc, char **argv) {
    struct sockaddr_in addrin;
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    int sock=bindedSocket("0.0.0.0", NULL,SOCK_STREAM,&addrin);
    printf("%d , %s\n",ntohs(addrin.sin_port), inet_ntoa(addrin.sin_addr));
    printf("%s\n-----\n",getNameInfo(&addrin));
    if (getsockname(sock, (struct sockaddr *)&sin, &len) == -1)
    perror("getsockname");
    else {
      printf("%d , %s\n",ntohs(sin.sin_port), inet_ntoa(sin.sin_addr));
      printf("%s",getNameInfo(&sin));
    }
}
