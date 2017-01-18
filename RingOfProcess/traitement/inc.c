#include <stdio.h>
#include <unistd.h>
#define MAXBUFF 255

int traitement (int a) {
	return a+1;
}

int main () {
    
	int x;
        char c;
        int res;
	while(1) {
    		res = scanf("%d",&x);
                if (res==EOF) {
                   write(2,"Do nothing c'est ce n'est pas bon!",36);
                   exit(1);
                } else if (res==1){ 
                  //%d a résussi
    		  printf("%d\n",traitement(x));
                  fflush(stdout);
                } else {
                   //Une erreure  ou fin de ligne on essaye de réparrer
                   scanf("%c",&c);
                   if (c=='\n') {
                         //On trasmet new line pas de mal 
                         printf("%c",c);
                         fflush(stdout);
                   } else write(2,"Erreure ...", 12);
                } 
	}

}
