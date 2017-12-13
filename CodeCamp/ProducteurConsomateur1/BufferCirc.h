typedef struct _buffer_circ {
    int taille;
    int nb;
    int debut;
    int fin;
    void* *tab; //Tableau de type quelconque
} buffer_circ_t;

struct _buffer_circ *newBufferCirc(int taille); 
int ajouterBC(struct _buffer_circ *bc, void * elem);
void *retirer(struct _buffer_circ *bc);
void trace(struct _buffer_circ *bc);

extern struct _buffer_circ *buff;