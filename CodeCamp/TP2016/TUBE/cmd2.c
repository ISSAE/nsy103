#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
    char buffer[1024];
    int nbc;
    
    nbc=read(0,buffer,1024);
    
    buffer[nbc]=0;
    
    printf("PID:%d . J'ai lu %s\n",getpid(), buffer);
}
