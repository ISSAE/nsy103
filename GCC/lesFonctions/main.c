/* 
 * File:   main.c
 * Author: pascalfares
 *
 * Created on 26 octobre 2015, 10:18
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
 int a,b;

 a=10;
 b=20;
 printf("Avant : a=%d,b=%d\n",a,b);
 swap(&a,&b);

 printf("Après a=%d,b=%d fact(3)=%d code=%d\n",a,b,fact(3),EXIT_SUCCESS);

 return (10);
}
