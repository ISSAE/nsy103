#include <stdio.h>

int f(int *p) {
    
    *p=100;
    
    printf("%p : %d\n",p, *p);
    return 1;
}

int g(int p) {
    p=100;
    
    return 1;
}


int main(){
    int x;
    int y;
    int *px = &x;
    
    *px=200;
    
    printf("adresse de x=%p, valeur de px=%p, x=%d\n",&x, px, x);
    
    printf("%p : %d\n",&x, x);
    y=f(&x);
    printf("%p : %d\n",&x, x);
    x=10000;
    printf("x=%d res f(&x)=%d, adresse de x=%p valeur x=%d\n", x, f(&x), &x, x);
    
    printf("res g(y)=%d, valeur y=%d\n", g(y), y);
           
            
            
}