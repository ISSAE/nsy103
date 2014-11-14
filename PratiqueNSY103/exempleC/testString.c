#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(int argc, char** argv) {
     char s[10];
     s[0]='a';*(s+1)='0';s[2]='c';s[3]=0;
     char *s1=malloc(15);
     
     strcpy(s1,"abcdefg0123");

     int code0 = '0';

     printf("\ns=%s , s1=%s, code0=%0x %d %c\n", s, s1, code0, code0, code0);

    s1[5]=0;

    printf("\ns=%s , s1=%s, code0=%0x %ld %c\n", s, s1, '1', s, code0);

    printf("&s1=%ld s1=%s, code0=%0x %ld %c\n", s1, s1+6, '1', s, code0);

   s1=s; //c' est faut

   printf("s1=%s s=%s");

   

   
}
