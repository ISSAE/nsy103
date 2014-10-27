main () {
   int S[5][2] = {0,1,2,3,4,5,6,7,8,9};
   int i,j;
   /**
     * afficher tous les éléments
     */
   for (i=0; i < 5; i++)
      for (j=0; j <2; j++)
         printf("S[%d][%d]=%d\n",i,j,S[i][j]);
}
/** résultat de l'execution
compiler : gcc testtab.c 
lancer le programme ./a.out
S[0][0]=0
S[0][1]=1
S[1][0]=2
S[1][1]=3
S[2][0]=4
S[2][1]=5
S[3][0]=6
S[3][1]=7
S[4][0]=8
S[4][1]=9

*/
