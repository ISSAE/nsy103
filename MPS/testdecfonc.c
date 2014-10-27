int f(); /* signature d'une fonction renvoyant un entier */

int *g(); /* signature d'une fonction renvoyant un pointeur sur entier */

int w();
int (*k)(); /* pointeur sue une fonction renvoyant un entier */

/**
  * definition de la fonction f
  */
int f(int x, int y) {
    return (x+y);
}

int w(int (*s)(), int x, int y) {
   return ((*s)(x,y));
   /* dans gnu gcc on peur ecrite s(x,y) au lieu (*s)(x+y)
    * c'est peut-être plus clair!
    */
}

main () {
 k=f; /* on dit que k pointe sur la fonction f */

 printf("%d+%d=%d\n",3,5,k(3,5)); 
     /* l'utilisation de k est alors equivalente à f*/
 printf("%d+%d=%d\n",3,5,w(f,3,5)); 
}

/** resultat de l'execution (test)
compilation:
[pfares@pportable MPS]$ gcc testdecfonc.c
execution:
[pfares@pportable MPS]$ ./a.out
3+5=8
3+5=8
*/
