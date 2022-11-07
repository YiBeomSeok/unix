#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

void handler(int signo) {
  printf("Wake up\n");
}

void alarm_print_wakeup_message() {
  struct itimerval it;
  
  sigset(SIGALRM, handler);
  it.it_value.tv_sec = 1;
  it.it_value.tv_usec = 0;
  it.it_interval.tv_sec = 1;
  it.it_interval.tv_usec = 0;

  if (setitimer(ITIMER_REAL, &it, (struct itimerval *)NULL) == -1) {
    perror("settimer");
    exit(1);
  }
}

int main() {
  sigset_t signalset;
  sigemptyset(&signalset);

  sigfillset(&signalset);
  sigdelset(&signalset, SIGINT);
  sigdelset(&signalset, SIGALRM);

  sigprocmask(SIG_BLOCK, &signalset, (sigset_t *)NULL);

  alarm_print_wakeup_message();

  while(1) {
    pause();
    alarm(2);
  }

  printf("end\n");

  return 0;
}