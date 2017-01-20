#include <stdio.h>

#define MAXBUFF 255

int traitement (int a) {
	return a+1;
}

int main (int argc, char** argv) {
        char buff[MAXBUFF];
        char c;
        int f,t; 
	int x; 
	while(1) {
                c=getchar();
                if ((c>='0') && (c<='9')) 
                putchar(++c);
                else putchar ('x');
	}

}
