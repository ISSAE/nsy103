struct _list {
    int valeur;
    struct _list *suiv;
};

typedef struct _list list;
typedef list *plist;

plist new();
plist cons(int v, plist reste);
plist reste(plist l);
int tete(plist l);
plist find(int v, plist l);
plist findPrec(int v, plist l);
plist suprime(int v, plist l);
void printList(plist l);





