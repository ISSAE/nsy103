/* une procedure qui devrait échanger les contenus de x et y */

void swap (int *x, int *y) {
     int z=*x;
     *x=*y;
     *y=z;
}

int fact(int n) {
  if (n==0) return 1;
  else return n*fact(n-1);
}

