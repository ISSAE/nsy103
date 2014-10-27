/* loadhello.c -- chargement explicite de print_hello depuis libhello.so */
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*hello_function)(void);

int main (void) {
   void *library;
   hello_function hello;
   const char *error;

   library = dlopen("libhello.so", RTLD_LAZY);
   if (library == NULL) {
      fprintf(stderr, "ne peut ouvrir libhello.so: %s\n", dlerror());
      exit(1);
   }

   /* while in this case we know that the print_hello symbol
    * should never be null, that is not true for looking up
    * arbitrary symbols.  So we demonstrate checking dlerror()'s
    * return code instead of dlsym()'s.
    */
   dlerror();
   /** On récupère le pointeur de la fonction print_hello
    */
   hello = dlsym(library, "print_hello");
   error = dlerror();
   if (error) {
      fprintf(stderr, "ne peut trouver print_hello: %s\n", error);
      exit(1);
   }


   /**
    * Appel de la fonction
    */
   (*hello)();
   dlclose(library);
   return 0;
}
