void main(int argc, char **argv) {
  int x = 0;

  printf("%d --x est: %d\n", getpid(), x);
  fork();
  x++;
  fork();
  x++;
  printf("%d --x est: %d adresse est %p\n", getpid(), x, &x);
}
