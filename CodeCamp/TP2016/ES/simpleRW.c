#include <unistd.h>

int main (){
    char buffer[256];
    int nbc;
    
    write(1, "> ", 2);
    
    nbc = read(0, buffer, 256);
    
    write(1, buffer, 2);
    
    write(1, "...", 3);
    
    write(1, buffer+2,(nbc-2));
    
    write(1, "\nFIN\n", 5);
}
