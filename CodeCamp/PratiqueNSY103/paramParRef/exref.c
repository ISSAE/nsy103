#include <stdio.h>

//Une fonction
int plus (int x, int y) {
    int res = x+y;
    x=y;
    return res;
}

int mult (int x, int y) {
    int res = x*y;
    x=y;
    return res;
}

int doSomething(int (*f)(int, int), int a, int b) {
    return (f(a,b));
}
//Une procedure
void bplus(int x, int y, int *res) {
	*res=x+y;
}

main (int argc, char** argv) {
     int a=10;
     int b=20;
     int r;

     r=plus(a,b);
     printf("plus %d+%d=%d\n", a, b, r);
     a=b=100;
     bplus(a,b,&r);
     printf("bplus %d+%d=%d\n", a, b, r);
     printf("\n==== appel indirect\n");
     printf("? %d ? %d=%d\n", a, b, doSomething(plus,a,b));
     printf("? %d ? %d=%d\n", a, b, doSomething(mult,a,b));


}
