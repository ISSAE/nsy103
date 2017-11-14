void main(int argc, char **argv) {
      int x=0;
      int pid;

      printf("%d --x est: %d\n", getpid(), x);
      pid = fork();
      if (pid == 0) x++;
      printf("%d --x est: %d adresse est %p\n", getpid(), x, &x);
      pid= fork();
      if (pid == 0) x++;
      printf("%d --x est: %d adresse est %p\n", getpid(), x, &x);

}
