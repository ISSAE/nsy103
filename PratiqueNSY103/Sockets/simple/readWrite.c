#include <stdio.h>
#include <strings.h>

int readWrite(int fd) {
     int n;
     char buffer[256];
     bzero(buffer,256);
     n = read(fd,buffer,255);
     if (n < 0) return n;
     printf("Here is the message: %s\n",buffer);
     n = write(fd,"I got your message",18);
     if (n < 0) return n;
}
