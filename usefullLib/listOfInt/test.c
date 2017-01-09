#include "list.h"
#include <stdio.h>

int main(int argc, char**argv){
    plist l = new();
    
    printList(l);
    
    l = cons(1,l);
    printList(l);
   
    l = cons(2,l);
    printList(l);
    l = cons(3,l);
    printList(l);
    l = cons(4,l);
    printList(l);
    printf("suprime 2");
    l=suprime(2,l);
    printList(l);
    printf("suprime 4");
    l=suprime(4,l);
    printList(l);
    printf("suprime 40\n");
    l=suprime(40,l);
    printList(l);
    printf("suprime 1");
    l=suprime(1,l);
    printList(l);
    printf("suprime 3");
    l=suprime(3,l);
    printList(l);
   
    
}