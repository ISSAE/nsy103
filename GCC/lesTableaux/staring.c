#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
 char s[]="toto";
 int i;

 printf("Ma chaine est %s\n",s);

 s[1]='x';

 printf("Ma chaine est %s\n",s);

 s[4]='y';
 printf("Ma chaine est %s\n",s);

 s[2]=0;

  printf("Ma chaine est %s\n",s);

s[2]=50;

 printf("Ma chaine est %s\n",s);

 for (i=1; i< 255; i++) {
     printf("caractère codeBase10=%d codeHexa=%x asscii=%c\n",i,i,i);
 }
 return (EXIT_SUCCESS);
}
