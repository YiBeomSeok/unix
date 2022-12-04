#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>

void handler(int signo) {
  psignal(signo, "Received Signal");
}

int main(void) {
  struct itimerval it;
  
  sigset(SIGALRM, handler);
  it.it_value.tv_sec = 3;
  it.it_value.tv_usec = 0;
  it.it_interval.tv_sec = 2;
  it.it_interval.tv_usec = 0;

  if(settimer(ITIMER_REAL, &it, (struct itimerval *)NULL) == -1) {
      perror("settimer");
      exit(1);
  }

  while(1) {
    getitimer
  }

}