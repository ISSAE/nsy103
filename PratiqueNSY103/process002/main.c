#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "plus.h"

main() {
      int x=100;
      int j;
      int res=fork();
      if (res >0) {
           //tabPlus(10,10);
            printf("je suis le père pid= %d, ppid= %d\n",getpid(), getppid());
             for (j=x;j<200;j++) printf("père %d",j);
     
      } else if (res ==0) {
            //tabPlus(2,2);
            printf("je suis le fils pid= %d, ppid= %d\n",getpid(), getppid());
      for (j=x;j>=0;j--) printf("fils %d",j);
      } else {
           printf("Erreure :(");
      }
}
