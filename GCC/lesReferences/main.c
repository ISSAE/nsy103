/* 
 * File:   main.c
 * Author: pascalfares
 *
 * Created on 26 octobre 2015, 09:16
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Une variable est définie par un nom et une adresse en mémoire
 * [Nom,Adresse] pr exemple [x,&x] &x signifie adresse de x
 * Une variable possède une valeur, pour y acceder on utilise soit le nom de la variable,
 * soit *Adresse
 * L'instruction de changement d'état, l'affectation permet de modifier les valeurs
 * exemple x=10; ou encore *(&x)=10 !
 */
int main(int argc, char** argv) {
    int x=10;
    /* Une variables x est pacée en MC à une certaine adresse mémoire */
    /* En C on peut récupéré cette adresse grace à l'opérateur &*/
    printf("Une variables est placée en MC à une certaine adresse mémoire\nEn C on peut récupéré cette adresse grace à l'opérateur &\n");
    printf("1-La variable x est à l'adresse %p et a la valeur %d\n", &x,x);
    
    /* On peut affecter aussi les adresses dans des variables */
    
    int* p; /* p est de type adresse ou pointeur : une référence*/
    
    p = &x;
    
    printf("2-La variable x est à l'adresse %p et a la valeur %d\n", p,x);
    
    /* a partir d'une adresse on peut aussi acceder a la valeur de la case mémoire operateur * */
    
    printf("3-La mémoire à l'adresse %p a la valeur %d\n", p, *p);
    
    /* Affectation de valeur par référnece au nom de l variable*/
    x=100;
    
    printf("valeur x=%d, adresse x=%p\n",*p,p);
    
    /* Affectation de valeur par référnece à l'adresse de l variable*/
    
    *p=500;
    
     printf("valeur x=%d, adresse x=%p\n",x,p);
    
    return (EXIT_SUCCESS);
}

