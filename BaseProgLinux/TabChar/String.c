#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    char  str1[]="emile-pascal";

    char *str;

    str= (char *) malloc(6*sizeof(char));
    strcpy(str,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    strncpy(str,"pascal",3);

    printf("%s %s\n",str, str1);

    str[2]='0';

    str[4]='\0';

    printf("%d %c %s \n",'0', '0', str);

}
