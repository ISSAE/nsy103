#include <stdio.h>

#define MAXBUFF 255

int traitement (int a) {
	return a+1;
}

int main () {
    
	int x; 
	while(1) {
    		scanf("%d",&x );
    		printf("%d",traitement(x));
	}

}
