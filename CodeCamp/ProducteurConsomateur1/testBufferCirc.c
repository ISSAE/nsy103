#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "BufferCirc.h"

int main() {
    int i;
    struct _buffer_circ *buff = newBufferCirc(10);
    void* elem;
    //ajouter 10 éléments
    for (i=0;i<15;i++) {
        ajouterBC(buff, (void *)(intptr_t)(i+1));
        trace(buff);
    }
    for (i=0;i<11;i++) {
        elem=retirer(buff);
        printf("li %p",elem);
        trace(buff);
        
    }
}