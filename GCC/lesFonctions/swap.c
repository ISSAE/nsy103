/* une procedure qui devrait échanger les contenus de x et y */

void swap (int x, int y) {
     int z=x;
     printf("debut swap %d %d\n",x,y);
     x=y;
     y=z;
     printf("fin swap %d %d\n",x,y);
}

int fact(int n) {
  if (n==0) return 1;
  else return n*fact(n-1);
}

