#include <stdio.h>

unsigned long
hash1(char const *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) | hash) | c; /* hash * 33 + c */
    }

    return hash;
}

int hash(char const *input) { 
    return (hash1(input)%100);
}

int main (int argc, char **argv) {
    printf("hash1 = %ld , hash2= %d\n", hash1(argv[1]), hash(argv[1]));

}
