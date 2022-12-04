#include <sys/types.h>
#include <sys/times.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int i;
  time_t t;
  struct tms mytms;
  clock_t t1, t2;
  
  if ((t1 - times(&mytms)) == -1) {
    perror("times 1");
    exit(1);
  }

  for (i = 0; i < 999999; i++) {
    times(&mytms);
  }
}
